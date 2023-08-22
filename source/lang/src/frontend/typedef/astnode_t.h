#ifndef _astnode_t_h
#define _astnode_t_h

/**
 * @brief Holding the different types of nodes
 * 
 */
typedef enum {
    Program_Node,
    NumericLiteral_Node,
    Identifier_Node,
    BinaryExpression_Node,

    // for linked list head/tail nodes
    LL_EMPTY
} NodeType;

/**
 * @brief Base statement "interface" for implementation. Does not result
 * in a value at runtime
 * 
 */
typedef struct StatementNode {
    NodeType kind;
} Statement;


/**
 * @brief TokenNode struct definition
 *
 * This is a single node for the linked list, and really has nothing to do with
 * the 'Node' in 'NodeType' for AST nodes
 *
 */
typedef struct Array_StmtNode { 
    Statement stmt;
    struct Array_StmtNode* next;
} sNode;

/**
 * @brief Base expression interface for implementation. Does result in a
 * value at runtime
 * 
 */
typedef struct ExpressionBaseNode {
    Statement* exprKind;
} Expression;

/**
 * @brief Program handle. Implements statement with field once initialized.
 *
 * The program body is an array of statements
 * 
 */
typedef struct ProgramNode {
    Statement* stmtKind;
    Array* body;
} Program;

/**
 * @brief Binary expression implementation
 * 
 */
typedef struct BinaryExprNode {
    Expression* exprKind;
    Expression* left;
    Expression* right;
    char* operation; // needs to be of type BinaryOperator
} BinExpr;

/**
 * @brief Identifier implementation
 * 
 */
typedef struct IdentifierNode {
    Expression* exprKind;
    char* string;
} Ident;

/**
 * @brief NumericLiteralNode implementation
 * 
 */
typedef struct NumericLiteralNode {
    Expression* exprKind;
    double value;
} NumLit;

#endif
