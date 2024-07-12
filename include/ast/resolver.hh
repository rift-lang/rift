/////////////////////////////////////////////////////////////
///                                                       ///
///     ██████╗ ██╗███████╗████████╗                      ///
///     ██╔══██╗██║██╔════╝╚══██╔══╝                      ///
///     ██████╔╝██║█████╗     ██║                         ///
///     ██╔══██╗██║██╔══╝     ██║                         ///
///     ██║  ██║██║██║        ██║                         ///
///     ╚═╝  ╚═╝╚═╝╚═╝        ╚═╝                         ///
///     * RIFT CORE - The official compiler for Rift.     ///
///     * Copyright (c) 2024, Rift-Org                    ///
///     * License terms may be found in the LICENSE file. ///
///                                                       ///
/////////////////////////////////////////////////////////////

#include <unordered_map>
#include <stack>
#include <ast/eval.hh>

using std::stack;
using std::unordered_map;
using std::string;
using std::vector;

namespace rift
{
    namespace ast
    {
        
        class Resolver : public ExprVisitor<Token>, StmtVisitor<Token>, 
                                DeclVisitor<Token>, ProgramVisitor<Tokens>
        {
            public:
                Resolver() = default;
                virtual ~Resolver() = default;

                enum FunctionType
                {
                    NONE,
                    FUNCTION,
                    INITALIZER,
                    METHOD
                };

                friend class Eval;

                // expressions
                Token visit_assign(const Assign<Token>& expr) const override;
                Token visit_binary(const Binary<Token>& expr) const override;
                Token visit_grouping(const Grouping<Token>& expr) const override;
                Token visit_literal(const Literal<Token>& expr) const override;
                Token visit_var_expr(const VarExpr<Token>& expr) const override;
                Token visit_unary(const Unary<Token>& expr) const override;
                Token visit_ternary(const Ternary<Token>& expr) const override;
                Token visit_call(const Call<Token>& expr) const override;

                // statements
                Token visit_expr_stmt(const StmtExpr<Token>& stmt) const override;
                Token visit_print_stmt(const StmtPrint<Token>& stmt) const override;
                Token visit_if_stmt(const StmtIf<Token>& stmt) const override;
                Token visit_return_stmt(const StmtReturn<Token>& stmt) const override;
                Token visit_block_stmt(const Block<Token>& block) const override;
                Token visit_for_stmt(const For<Token>& decl) const override;

                // declarations
                Token visit_decl_stmt(const DeclStmt<Token>& decl) const override;
                Token visit_decl_var(const DeclVar<Token>& decl) const override;
                Token visit_decl_func(const DeclFunc<Token>& decl) const override;

                // program
                Tokens visit_program(const Program<Tokens>& prgm) const override;

            private:
                FunctionType f_type = NONE;
        };

        // ERROR
        class ResolverException : public std::exception
        {
            public:
                ResolverException(const string &message): message(message) {};
                const char *what() const noexcept override { return message.c_str(); }
            private:
                string message;
        };

    }
}