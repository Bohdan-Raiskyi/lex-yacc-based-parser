%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

// Value type for evaluation
typedef struct Value {
    int type; // 0 = int, 1 = float, 2 = undefined, 3 = bool
    union {
        int int_val;
        float float_val;
        int bool_val;
    };
} Value;

// AST Node Types
typedef enum {
    NODE_PROGRAM,
    NODE_DECLARATION,
    NODE_ASSIGNMENT,
    NODE_RETURN,
    NODE_BINARY_OP,
    NODE_IDENTIFIER,
    NODE_INT_CONSTANT,
    NODE_FLOAT_CONSTANT,
    NODE_COMPOUND_STMT,
    NODE_IF,
    NODE_EQ,
    NODE_NE,
    NODE_GT,
    NODE_LT,
    NODE_GE,
    NODE_LE,
    NODE_AND,
    NODE_OR,
    NODE_NOT
} NodeType;

// AST Node Structure
typedef struct ASTNode {
    NodeType type;
    char* name;  // For identifiers
    union {
        int int_value;
        float float_value;
        int bool_value;
    };
    struct ASTNode* left;
    struct ASTNode* right;
    struct ASTNode* next; // For linked lists (statements)
    struct ASTNode* else_branch; // For if-else statements
} ASTNode;

// Symbol table for evaluation
typedef struct Symbol {
    char* name;
    Value value;
    int initialized;
} Symbol;

#define MAX_SYMBOLS 100
Symbol symbol_table[MAX_SYMBOLS];
int symbol_count = 0;

// Global root of AST
ASTNode* root = NULL;

// Function declarations
ASTNode* create_node(NodeType type);
ASTNode* create_int_node(int value);
ASTNode* create_float_node(float value);
ASTNode* create_identifier_node(char* name);
ASTNode* create_binary_op_node(NodeType op, ASTNode* left, ASTNode* right);
ASTNode* create_unary_op_node(NodeType op, ASTNode* operand);
ASTNode* create_if_node(ASTNode* condition, ASTNode* then_branch, ASTNode* else_branch);
void free_ast(ASTNode* node);
void print_ast(ASTNode* node, int depth);
void generate_code(ASTNode* node, FILE* output);
Value evaluate_expression(ASTNode* node);

extern int line_num;
extern FILE *yyin;
void yyerror(const char *s);
int yylex(void);

%}

%union {
    int int_val;
    float float_val;
    char* string_val;
    struct ASTNode* node;
}

%token <int_val> INT_CONSTANT
%token <float_val> FLOAT_CONSTANT
%token <string_val> IDENTIFIER
%token INT FLOAT RETURN IF ELSE
%token LBRACE RBRACE LPAREN RPAREN SEMICOLON ASSIGN
%token PLUS MINUS MULTIPLY DIVIDE
%token EQ NE GT LT GE LE AND OR NOT
%token ERROR

%type <node> program statement_list statement declaration assignment expression
%type <node> compound_statement if_statement
%type <node> logical_or_expression logical_and_expression equality_expression
%type <node> relational_expression additive_expression multiplicative_expression primary_expression

%start program

%right ASSIGN
%left OR
%left AND
%left EQ NE
%left GT LT GE LE
%left PLUS MINUS
%left MULTIPLY DIVIDE
%right NOT

%%

program:
    statement_list {
        $$ = create_node(NODE_PROGRAM);
        $$->left = $1;
        root = $$;
    }
    ;

statement_list:
    statement {
        $$ = $1;
    }
    | statement_list statement {
        struct ASTNode* current = $1;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = $2;
        $$ = $1;
    }
    ;

statement:
    declaration {
        $$ = $1;
    }
    | assignment {
        $$ = $1;
    }
    | if_statement {
        $$ = $1;
    }
    | compound_statement {
        $$ = $1;
    }
    ;

declaration:
    INT IDENTIFIER SEMICOLON {
        $$ = create_node(NODE_DECLARATION);
        $$->name = $2;
    }
    | FLOAT IDENTIFIER SEMICOLON {
        $$ = create_node(NODE_DECLARATION);
        $$->name = $2;
    }
    | INT IDENTIFIER ASSIGN expression SEMICOLON {
        $$ = create_node(NODE_DECLARATION);
        $$->name = $2;
        $$->left = $4;
    }
    | FLOAT IDENTIFIER ASSIGN expression SEMICOLON {
        $$ = create_node(NODE_DECLARATION);
        $$->name = $2;
        $$->left = $4;
    }
    ;

assignment:
    IDENTIFIER ASSIGN expression SEMICOLON {
        $$ = create_node(NODE_ASSIGNMENT);
        $$->name = $1;
        $$->left = $3;
    }
    ;

if_statement:
    IF LPAREN expression RPAREN statement {
        $$ = create_if_node($3, $5, NULL);
    }
    | IF LPAREN expression RPAREN statement ELSE statement {
        $$ = create_if_node($3, $5, $7);
    }
    ;

compound_statement:
    LBRACE statement_list RBRACE {
        $$ = create_node(NODE_COMPOUND_STMT);
        $$->left = $2;
    }
    | LBRACE RBRACE {
        $$ = create_node(NODE_COMPOUND_STMT);
    }
    ;

expression:
    logical_or_expression
    ;

logical_or_expression:
    logical_and_expression
    | logical_or_expression OR logical_and_expression {
        $$ = create_binary_op_node(NODE_OR, $1, $3);
    }
    ;

logical_and_expression:
    equality_expression
    | logical_and_expression AND equality_expression {
        $$ = create_binary_op_node(NODE_AND, $1, $3);
    }
    ;

equality_expression:
    relational_expression
    | equality_expression EQ relational_expression {
        $$ = create_binary_op_node(NODE_EQ, $1, $3);
    }
    | equality_expression NE relational_expression {
        $$ = create_binary_op_node(NODE_NE, $1, $3);
    }
    ;

relational_expression:
    additive_expression
    | relational_expression GT additive_expression {
        $$ = create_binary_op_node(NODE_GT, $1, $3);
    }
    | relational_expression LT additive_expression {
        $$ = create_binary_op_node(NODE_LT, $1, $3);
    }
    | relational_expression GE additive_expression {
        $$ = create_binary_op_node(NODE_GE, $1, $3);
    }
    | relational_expression LE additive_expression {
        $$ = create_binary_op_node(NODE_LE, $1, $3);
    }
    ;

additive_expression:
    multiplicative_expression
    | additive_expression PLUS multiplicative_expression {
        $$ = create_binary_op_node(NODE_BINARY_OP, $1, $3);
    }
    | additive_expression MINUS multiplicative_expression {
        $$ = create_binary_op_node(NODE_BINARY_OP, $1, $3);
    }
    ;

multiplicative_expression:
    primary_expression
    | multiplicative_expression MULTIPLY primary_expression {
        $$ = create_binary_op_node(NODE_BINARY_OP, $1, $3);
    }
    | multiplicative_expression DIVIDE primary_expression {
        $$ = create_binary_op_node(NODE_BINARY_OP, $1, $3);
    }
    ;

primary_expression:
    IDENTIFIER {
        $$ = create_identifier_node($1);
    }
    | INT_CONSTANT {
        $$ = create_int_node($1);
    }
    | FLOAT_CONSTANT {
        $$ = create_float_node($1);
    }
    | LPAREN expression RPAREN {
        $$ = $2;
    }
    | NOT primary_expression {
        $$ = create_unary_op_node(NODE_NOT, $2);
    }
    ;

%%

// AST Creation Functions
ASTNode* create_node(NodeType type) {
    ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
    node->type = type;
    node->name = NULL;
    node->int_value = 0;
    node->float_value = 0.0f;
    node->bool_value = 0;
    node->left = node->right = node->next = node->else_branch = NULL;
    return node;
}

ASTNode* create_int_node(int value) {
    ASTNode* node = create_node(NODE_INT_CONSTANT);
    node->int_value = value;
    return node;
}

ASTNode* create_float_node(float value) {
    ASTNode* node = create_node(NODE_FLOAT_CONSTANT);
    node->float_value = value;
    return node;
}

ASTNode* create_identifier_node(char* name) {
    ASTNode* node = create_node(NODE_IDENTIFIER);
    node->name = strdup(name);
    return node;
}

ASTNode* create_binary_op_node(NodeType op, ASTNode* left, ASTNode* right) {
    ASTNode* node = create_node(op);
    node->left = left;
    node->right = right;
    return node;
}

ASTNode* create_unary_op_node(NodeType op, ASTNode* operand) {
    ASTNode* node = create_node(op);
    node->left = operand;
    return node;
}

ASTNode* create_if_node(ASTNode* condition, ASTNode* then_branch, ASTNode* else_branch) {
    ASTNode* node = create_node(NODE_IF);
    node->left = condition;
    node->right = then_branch;
    node->else_branch = else_branch;
    return node;
}

void free_ast(ASTNode* node) {
    if (node == NULL) return;
    
    free_ast(node->left);
    free_ast(node->right);
    free_ast(node->next);
    free_ast(node->else_branch);
    
    if (node->name != NULL) {
        free(node->name);
    }
    
    free(node);
}

// AST Printing Function
void print_ast(ASTNode* node, int depth) {
    if (node == NULL) {
        return;
    }
    
    for (int i = 0; i < depth; i++) {
        printf("  ");
    }
    
    switch (node->type) {
        case NODE_PROGRAM:
            printf("PROGRAM\n");
            print_ast(node->left, depth + 1);
            break;
        case NODE_DECLARATION:
            printf("DECLARATION: %s\n", node->name);
            if (node->left != NULL) {
                print_ast(node->left, depth + 1);
            }
            break;
        case NODE_ASSIGNMENT:
            printf("ASSIGNMENT: %s\n", node->name);
            print_ast(node->left, depth + 1);
            break;
        case NODE_RETURN:
            printf("RETURN\n");
            print_ast(node->left, depth + 1);
            break;
        case NODE_BINARY_OP:
            printf("BINARY_OP\n");
            print_ast(node->left, depth + 1);
            print_ast(node->right, depth + 1);
            break;
        case NODE_IDENTIFIER:
            printf("IDENTIFIER: %s\n", node->name);
            break;
        case NODE_INT_CONSTANT:
            printf("INT: %d\n", node->int_value);
            break;
        case NODE_FLOAT_CONSTANT:
            printf("FLOAT: %f\n", node->float_value);
            break;
        case NODE_COMPOUND_STMT:
            printf("COMPOUND_STMT\n");
            print_ast(node->left, depth + 1);
            break;
        case NODE_IF:
            printf("IF\n");
            print_ast(node->left, depth + 1);
            print_ast(node->right, depth + 1);
            if (node->else_branch != NULL) {
                for (int i = 0; i < depth; i++) printf("  ");
                printf("ELSE\n");
                print_ast(node->else_branch, depth + 1);
            }
            break;
        case NODE_EQ:
            printf("EQ (==)\n");
            print_ast(node->left, depth + 1);
            print_ast(node->right, depth + 1);
            break;
        case NODE_NE:
            printf("NE (!=)\n");
            print_ast(node->left, depth + 1);
            print_ast(node->right, depth + 1);
            break;
        case NODE_GT:
            printf("GT (>)\n");
            print_ast(node->left, depth + 1);
            print_ast(node->right, depth + 1);
            break;
        case NODE_LT:
            printf("LT (<)\n");
            print_ast(node->left, depth + 1);
            print_ast(node->right, depth + 1);
            break;
        case NODE_GE:
            printf("GE (>=)\n");
            print_ast(node->left, depth + 1);
            print_ast(node->right, depth + 1);
            break;
        case NODE_LE:
            printf("LE (<=)\n");
            print_ast(node->left, depth + 1);
            print_ast(node->right, depth + 1);
            break;
        case NODE_AND:
            printf("AND (&&)\n");
            print_ast(node->left, depth + 1);
            print_ast(node->right, depth + 1);
            break;
        case NODE_OR:
            printf("OR (||)\n");
            print_ast(node->left, depth + 1);
            print_ast(node->right, depth + 1);
            break;
        case NODE_NOT:
            printf("NOT (!)\n");
            print_ast(node->left, depth + 1);
            break;
    }
    
    if (node->next != NULL) {
        print_ast(node->next, depth);
    }
}

// Symbol Table Functions
int find_symbol(char* name) {
    for (int i = 0; i < symbol_count; i++) {
        if (strcmp(symbol_table[i].name, name) == 0) {
            return i;
        }
    }
    return -1;
}

int add_symbol(char* name, Value value) {
    if (find_symbol(name) != -1) return 0;
    
    if (symbol_count < MAX_SYMBOLS) {
        symbol_table[symbol_count].name = strdup(name);
        symbol_table[symbol_count].value = value;
        symbol_table[symbol_count].initialized = 1;
        symbol_count++;
        return 1;
    }
    return 0;
}

// Expression Evaluation
Value evaluate_expression(ASTNode* node) {
    Value result = {0};
    
    if (node == NULL) return result;
    
    switch (node->type) {
        case NODE_INT_CONSTANT:
            result.type = 0;
            result.int_val = node->int_value;
            break;
            
        case NODE_FLOAT_CONSTANT:
            result.type = 1;
            result.float_val = node->float_value;
            break;
            
        case NODE_IDENTIFIER: {
            int idx = find_symbol(node->name);
            if (idx != -1 && symbol_table[idx].initialized) {
                return symbol_table[idx].value;
            } else {
                fprintf(stderr, "Error: Variable '%s' not initialized\n", node->name);
                result.type = 2; // undefined
            }
            break;
        }
            
        case NODE_BINARY_OP: {
            Value left = evaluate_expression(node->left);
            Value right = evaluate_expression(node->right);
            
            if (left.type == 0 && right.type == 0) {
                result.type = 0;
                result.int_val = left.int_val + right.int_val; // Default to addition
            } else if ((left.type == 0 || left.type == 1) && (right.type == 0 || right.type == 1)) {
                result.type = 1;
                float lval = (left.type == 0) ? (float)left.int_val : left.float_val;
                float rval = (right.type == 0) ? (float)right.int_val : right.float_val;
                result.float_val = lval + rval; // Default to addition
            }
            break;
        }
            
        case NODE_EQ:
        case NODE_NE:
        case NODE_GT:
        case NODE_LT:
        case NODE_GE:
        case NODE_LE:
        case NODE_AND:
        case NODE_OR:
        case NODE_NOT: {
            // Simplified evaluation - in real implementation would need proper comparison
            Value left = evaluate_expression(node->left);
            Value right = evaluate_expression(node->right);
            result.type = 3; // bool
            result.bool_val = 1; // placeholder
            break;
        }
            
        default:
            result.type = 2; // undefined
            break;
    }
    
    return result;
}

// Code Generation
void generate_code(ASTNode* node, FILE* output) {
    if (node == NULL) {
        return;
    }
    
    switch (node->type) {
        case NODE_PROGRAM:
            fprintf(output, "#include <stdio.h>\n\n");
            fprintf(output, "int main() {\n");
            generate_code(node->left, output);
            fprintf(output, "    return 0;\n");
            fprintf(output, "}\n");
            break;
            
        case NODE_DECLARATION:
            if (node->name != NULL) {
                fprintf(output, "    int %s", node->name);
                if (node->left != NULL) {
                    fprintf(output, " = ");
                    generate_code(node->left, output);
                }
                fprintf(output, ";\n");
            }
            break;
            
        case NODE_ASSIGNMENT:
            if (node->name != NULL) {
                fprintf(output, "    %s = ", node->name);
                generate_code(node->left, output);
                fprintf(output, ";\n");
            }
            break;
            
        case NODE_INT_CONSTANT:
            fprintf(output, "%d", node->int_value);
            break;
            
        case NODE_FLOAT_CONSTANT:
            fprintf(output, "%f", node->float_value);
            break;
            
        case NODE_IDENTIFIER:
            fprintf(output, "%s", node->name);
            break;
            
        case NODE_BINARY_OP:
            fprintf(output, "(");
            generate_code(node->left, output);
            fprintf(output, " + "); // Simplified - should check actual operator
            generate_code(node->right, output);
            fprintf(output, ")");
            break;
            
        case NODE_COMPOUND_STMT:
            fprintf(output, "{\n");
            generate_code(node->left, output);
            fprintf(output, "}\n");
            break;
            
        case NODE_IF:
            fprintf(output, "if (");
            generate_code(node->left, output);
            fprintf(output, ") ");
            generate_code(node->right, output);
            if (node->else_branch != NULL) {
                fprintf(output, " else ");
                generate_code(node->else_branch, output);
            }
            break;
            
        case NODE_EQ:
            fprintf(output, "(");
            generate_code(node->left, output);
            fprintf(output, " == ");
            generate_code(node->right, output);
            fprintf(output, ")");
            break;
            
        case NODE_NE:
            fprintf(output, "(");
            generate_code(node->left, output);
            fprintf(output, " != ");
            generate_code(node->right, output);
            fprintf(output, ")");
            break;
            
        case NODE_GT:
            fprintf(output, "(");
            generate_code(node->left, output);
            fprintf(output, " > ");
            generate_code(node->right, output);
            fprintf(output, ")");
            break;
            
        case NODE_LT:
            fprintf(output, "(");
            generate_code(node->left, output);
            fprintf(output, " < ");
            generate_code(node->right, output);
            fprintf(output, ")");
            break;
            
        case NODE_GE:
            fprintf(output, "(");
            generate_code(node->left, output);
            fprintf(output, " >= ");
            generate_code(node->right, output);
            fprintf(output, ")");
            break;
            
        case NODE_LE:
            fprintf(output, "(");
            generate_code(node->left, output);
            fprintf(output, " <= ");
            generate_code(node->right, output);
            fprintf(output, ")");
            break;
            
        case NODE_AND:
            fprintf(output, "(");
            generate_code(node->left, output);
            fprintf(output, " && ");
            generate_code(node->right, output);
            fprintf(output, ")");
            break;
            
        case NODE_OR:
            fprintf(output, "(");
            generate_code(node->left, output);
            fprintf(output, " || ");
            generate_code(node->right, output);
            fprintf(output, ")");
            break;
            
        case NODE_NOT:
            fprintf(output, "(!");
            generate_code(node->left, output);
            fprintf(output, ")");
            break;
            
        default:
            fprintf(stderr, "CODEGEN: Unknown node type: %d\n", node->type);
            break;
    }
    
    if (node->next != NULL) {
        generate_code(node->next, output);
    }
}

void yyerror(const char *s) {
    fprintf(stderr, "PARSER ERROR at line %d: %s\n", line_num, s);
}

int main(int argc, char** argv) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <input_file> [output_file]\n", argv[0]);
        return 1;
    }
    
    FILE* input = fopen(argv[1], "r");
    if (!input) {
        fprintf(stderr, "ERROR: Cannot open input file: %s\n", argv[1]);
        return 1;
    }
    
    fseek(input, 0, SEEK_END);
    long size = ftell(input);
    fseek(input, 0, SEEK_SET);
    
    if (size == 0) {
        fprintf(stderr, "ERROR: File is empty\n");
        fclose(input);
        return 1;
    }
    
    yyin = input;
    
    printf("Parsing file: %s\n", argv[1]);
    
    root = NULL;
    int parse_result = yyparse();
    
    fclose(input);
    
    if (parse_result == 0) {
        if (root == NULL) {
            printf("WARNING: Parsing succeeded but root is NULL!\n");
        } else {
            printf("\n=== AST STRUCTURE ===\n");
            print_ast(root, 0);
            
            FILE* output = stdout;
            if (argc > 2) {
                output = fopen(argv[2], "w");
                if (!output) {
                    fprintf(stderr, "Cannot open output file: %s\n", argv[2]);
                    output = stdout;
                }
            }
            
            printf("\n=== GENERATED C CODE ===\n");
            generate_code(root, output);
            
            if (output != stdout) {
                fclose(output);
                printf("Code written to: %s\n", argv[2]);
            }
            
            free_ast(root);
            root = NULL;
        }
    } else {
        fprintf(stderr, "Parsing failed!\n");
    }
    
    return parse_result;
}