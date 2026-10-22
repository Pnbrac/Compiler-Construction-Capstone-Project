#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <tree.h>
#include <strtab.h>

#define PROGRAM 0
#define DECLLIST 1
#define DECL 2
#define VARDECL 3
#define TYPESPECIFIER 4
#define FUNDECL 5
#define FORMALDECLLIST 6
#define FORMALDECL 7
#define FUNBODY 8
#define LOCALDECLLIST 9
#define STATEMENTLIST 10
#define STATEMENT 11
#define COMPOUNDSTMT 12
#define ASSIGNSTMT 13
#define CONDSTMT 14
#define LOOPSTMT 15
#define RETURNSTMT 16
#define EXPRESSION 17
#define RELOP 18
#define ADDEXPR 19
#define ADDOP 20
#define TERM 21
#define MULOP 22
#define FACTOR 23
#define FUNCCALLEXPR 24
#define ARGLIST 25
#define INTEGER 26
#define IDENTIFIER 27
#define VAR 28
#define ARRAYDECL 29
#define CHAR 30
#define FUNCTYPENAME 31

enum opType {ADD, SUB, MUL, DIV, LT, LTE, EQ, GTE, GT, NEQ};

static FILE *out;
static int labelCounter = 0;

void genNode(tree *node);
void genStatement(tree *node);
void genFunction(tree *node);
void genVarDecl(tree *node);
void genAssign(tree *node);
void genIf(tree *node);
void genWhile(tree *node);
void genFor(tree *node);
void genReturn(tree *node);
const char *genExpr(tree *node);

void codegen(tree *root) {
    out = fopen("out.s", "w");

    if (out == NULL) {
        perror("Could not open out.s");
        exit(1);
    }

    fprintf(out, ".text\n");
    fprintf(out, ".globl main\n\n");

    genNode(root);

    fclose(out);
}

static int newLabel(void) {
    return labelCounter++;
}

void genNode(tree *node) {
    if (node == NULL) return;

    switch (node->nodeKind) {
        case PROGRAM:
        case DECLLIST:
        case DECL:
        case STATEMENTLIST:
        case STATEMENT:
        case COMPOUNDSTMT:
        case LOCALDECLLIST:

        case FUNBODY:
            for (int i = 0; i < node->numChildren; i++) {
                genNode(getChild(node, i));
            }
            break;

        case FUNDECL:
            genFunction(node);
            break;

        case VARDECL:
            genVarDecl(node);
            break;

        case ASSIGNSTMT:
            genAssign(node);
            break;

        case CONDSTMT:
            genIf(node);
            break;

        case LOOPSTMT:
            if (node->numChildren == 2) {
                genWhile(node);
            } else {
                genFor(node);
            }
            break;

        case RETURNSTMT:
            genReturn(node);
            break;

        default:
            break;
    }
}

static const char *regs[] = {"t0", "t1", "t2", "t3", "t4", "t5", "t6"};
static int regUsed[7] = {0};

static const char *getReg(void) {
    for (int i = 0; i < 7; i++) {
        if (!regUsed[i]) {
            regUsed[i] = 1;
            return regs[i];
        }
    }

    fprintf(stderr, "codegen error: out of registers\n");
    exit(1);
}

static void freeReg(const char *reg) {
    for (int i = 0; i < 7; i++) {
        if (strcmp(reg, regs[i]) == 0) {
            regUsed[i] = 0;
            return;
        }
    }
}

typedef struct {
    int symbolIndex;
    int offset;
    int size;      // number of elements
    int isArray;   // 1 = array, 0 = scalar
} VarOffset;

static VarOffset varOffsets[256];
static int varCount = 0;
static int nextOffset = -4;

static void resetFunctionLocals(void) {
    varCount = 0;
    nextOffset = -4;
    memset(regUsed, 0, sizeof(regUsed));
}

static int addVarOffset(int symbolIndex, int size, int isArray) {
    varOffsets[varCount].symbolIndex = symbolIndex;
    varOffsets[varCount].offset = nextOffset;
    varOffsets[varCount].size = size;
    varOffsets[varCount].isArray = isArray;

    if (isArray) {
        nextOffset -= size * 4;   // reserve full array space
    } else {
        nextOffset -= 4;          // reserve single int
    }

    varCount++;

    return varOffsets[varCount - 1].offset;
}

static int getVarOffset(int symbolIndex) {
    for (int i = varCount - 1; i >= 0; i--) {
        if (varOffsets[i].symbolIndex == symbolIndex) {
            return varOffsets[i].offset;
        }
    }

    fprintf(stderr, "codegen error: unknown variable symbol index %d\n", symbolIndex);
    exit(1);
}

void genFunction(tree *node) {
    tree *funcTypeName = getChild(node, 0);
    tree *idNode = getChild(funcTypeName, 1);

    char *name = get_symbol_id(idNode->val);

    resetFunctionLocals();

    fprintf(out, "%s:\n", name);
    fprintf(out, "    addi sp, sp, -256\n");
    fprintf(out, "    sw ra, 252(sp)\n");
    fprintf(out, "    sw s0, 248(sp)\n");
    fprintf(out, "    addi s0, sp, 256\n");

    for (int i = 1; i < node->numChildren; i++) {
        genNode(getChild(node, i));
    }

    fprintf(out, ".Lreturn_%s:\n", name);
    fprintf(out, "    lw ra, 252(sp)\n");
    fprintf(out, "    lw s0, 248(sp)\n");
    fprintf(out, "    addi sp, sp, 256\n");
    fprintf(out, "    ret\n\n");
}

void genVarDecl(tree *node) {
    tree *idNode = getChild(node, 1);

    if (node->numChildren == 3) {
        tree *arrayDecl = getChild(node, 2);

        int size = arrayDecl->val;

        addVarOffset(idNode->val, size, 1);  // array
    } else {
        addVarOffset(idNode->val, 1, 0);     // scalar
    }
}

static const char *genVarAddress(tree *varNode) {
    tree *idNode = getChild(varNode, 0);
    int baseOffset = getVarOffset(idNode->val);

    const char *addrReg = getReg();

    // Scalar variable: address is just s0 + offset
    if (varNode->numChildren == 1) {
        fprintf(out, "    addi %s, s0, %d\n", addrReg, baseOffset);
        return addrReg;
    }

    // Array element: address = base + index * 4
    const char *indexReg = genExpr(getChild(varNode, 1));

    fprintf(out, "    slli %s, %s, 2\n", indexReg, indexReg);
    fprintf(out, "    addi %s, s0, %d\n", addrReg, baseOffset);
    fprintf(out, "    sub %s, %s, %s\n", addrReg, addrReg, indexReg);

    freeReg(indexReg);
    return addrReg;
}

void genAssign(tree *node) {
    tree *varNode = getChild(node, 0);
    tree *exprNode = getChild(node, 1);

    const char *valueReg = genExpr(exprNode);
    const char *addrReg = genVarAddress(varNode);

    fprintf(out, "    sw %s, 0(%s)\n", valueReg, addrReg);

    freeReg(valueReg);
    freeReg(addrReg);
}

const char *genExpr(tree *node) {
    if (node == NULL) return NULL;

    switch (node->nodeKind) {
        case EXPRESSION:
            if (node->numChildren == 1) {
                return genExpr(getChild(node, 0));
            } else {
                const char *left = genExpr(getChild(node, 0));
                const char *right = genExpr(getChild(node, 2));
                const char *result = getReg();

                int op = getChild(node, 1)->val;

                switch (op) {
                    case LT:
                        fprintf(out, "    slt %s, %s, %s\n", result, left, right);
                        break;
                    case GT:
                        fprintf(out, "    slt %s, %s, %s\n", result, right, left);
                        break;
                    case LTE:
                        fprintf(out, "    slt %s, %s, %s\n", result, right, left);
                        fprintf(out, "    xori %s, %s, 1\n", result, result);
                        break;
                    case GTE:
                        fprintf(out, "    slt %s, %s, %s\n", result, left, right);
                        fprintf(out, "    xori %s, %s, 1\n", result, result);
                        break;
                    case EQ:
                        fprintf(out, "    sub %s, %s, %s\n", result, left, right);
                        fprintf(out, "    seqz %s, %s\n", result, result);
                        break;
                    case NEQ:
                        fprintf(out, "    sub %s, %s, %s\n", result, left, right);
                        fprintf(out, "    snez %s, %s\n", result, result);
                        break;
                }

                freeReg(left);
                freeReg(right);
                return result;
            }

        case ADDEXPR:
            if (node->numChildren == 1) {
                return genExpr(getChild(node, 0));
            } else {
                const char *left = genExpr(getChild(node, 0));
                const char *right = genExpr(getChild(node, 2));
                const char *result = getReg();

                if (getChild(node, 1)->val == ADD) {
                    fprintf(out, "    add %s, %s, %s\n", result, left, right);
                } else {
                    fprintf(out, "    sub %s, %s, %s\n", result, left, right);
                }

                freeReg(left);
                freeReg(right);
                return result;
            }

        case TERM:
            if (node->numChildren == 1) {
                return genExpr(getChild(node, 0));
            } else {
                const char *left = genExpr(getChild(node, 0));
                const char *right = genExpr(getChild(node, 2));
                const char *result = getReg();

                if (getChild(node, 1)->val == MUL) {
                    fprintf(out, "    mul %s, %s, %s\n", result, left, right);
                } else {
                    fprintf(out, "    div %s, %s, %s\n", result, left, right);
                }

                freeReg(left);
                freeReg(right);
                return result;
            }

        case FACTOR:
            return genExpr(getChild(node, 0));

        case INTEGER: {
            const char *reg = getReg();
            fprintf(out, "    li %s, %d\n", reg, node->val);
            return reg;
        }

        case CHAR: {
            const char *reg = getReg();
            fprintf(out, "    li %s, %d\n", reg, node->val);
            return reg;
        }

        case VAR: {
            const char *addrReg = genVarAddress(node);
            const char *valueReg = getReg();

            fprintf(out, "    lw %s, 0(%s)\n", valueReg, addrReg);

            freeReg(addrReg);
            return valueReg;
        }

        default:
            fprintf(stderr, "codegen error: unsupported expression node kind %d\n", node->nodeKind);
            exit(1);
    }
}

void genIf(tree *node) {
    int id = newLabel();

    const char *cond = genExpr(getChild(node, 0));

    if (node->numChildren == 2) {
        fprintf(out, "    beqz %s, .Lendif%d\n", cond, id);
        freeReg(cond);

        genNode(getChild(node, 1));

        fprintf(out, ".Lendif%d:\n", id);
    } else {
        fprintf(out, "    beqz %s, .Lelse%d\n", cond, id);
        freeReg(cond);

        genNode(getChild(node, 1));
        fprintf(out, "    j .Lendif%d\n", id);

        fprintf(out, ".Lelse%d:\n", id);
        genNode(getChild(node, 2));

        fprintf(out, ".Lendif%d:\n", id);
    }
}

void genWhile(tree *node) {
    int id = newLabel();

    fprintf(out, ".Lwhile%d:\n", id);

    const char *cond = genExpr(getChild(node, 0));
    fprintf(out, "    beqz %s, .Lendwhile%d\n", cond, id);
    freeReg(cond);

    genNode(getChild(node, 1));

    fprintf(out, "    j .Lwhile%d\n", id);
    fprintf(out, ".Lendwhile%d:\n", id);
}

void genFor(tree *node) {
    int id = newLabel();

    tree *init = getChild(node, 0);
    tree *cond = getChild(node, 1);
    tree *update = getChild(node, 2);
    tree *body = getChild(node, 3);

    // init
    genNode(init);

    fprintf(out, ".Lfor%d:\n", id);

    const char *condReg = genExpr(cond);
    fprintf(out, "    beqz %s, .Lendfor%d\n", condReg, id);
    freeReg(condReg);

    // body
    genNode(body);

    // update
    genNode(update);

    fprintf(out, "    j .Lfor%d\n", id);
    fprintf(out, ".Lendfor%d:\n", id);
}

void genReturn(tree *node) {
    if (node->numChildren > 0) {
        const char *reg = genExpr(getChild(node, 0));
        fprintf(out, "    mv a0, %s\n", reg);
        freeReg(reg);
    }

    fprintf(out, "    j .Lreturn_main\n");
}