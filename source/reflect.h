#line 13 "reflect.h2"
#include "parse.h"
#include "cpp2regex.h"

#ifndef REFLECT_H_CPP2
#define REFLECT_H_CPP2


//=== Cpp2 type declarations ====================================================


#include "cpp2util.h"

#line 1 "reflect.h2"

#line 20 "reflect.h2"
namespace cpp2 {

namespace meta {

#line 32 "reflect.h2"
class compiler_services;

#line 226 "reflect.h2"
class declaration_base;

#line 252 "reflect.h2"
class declaration;

#line 334 "reflect.h2"
class function_declaration;

#line 424 "reflect.h2"
class object_declaration;

#line 460 "reflect.h2"
class type_declaration;

#line 597 "reflect.h2"
class alias_declaration;

#line 1005 "reflect.h2"
class value_member_info;

#line 1561 "reflect.h2"
}

}


//=== Cpp2 type definitions and function declarations ===========================

#line 1 "reflect.h2"

//  Copyright 2022-2026 Herb Sutter
//  SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//  
//  Part of the Cppfront Project, under the Apache License v2.0 with LLVM Exceptions.
//  See https://github.com/hsutter/cppfront/blob/main/LICENSE for license information.


//===========================================================================
//  Reflection and meta
//===========================================================================

#include "parse.h"

#line 20 "reflect.h2"
namespace cpp2 {

namespace meta {

#line 25 "reflect.h2"
//-----------------------------------------------------------------------
//
//  Compiler services
//
//-----------------------------------------------------------------------
//

class compiler_services
 {

#line 33 "reflect.h2"
    private: std::vector<error_entry>* errors; 
    private: std::set<std::string>* includes; 
    private: std::vector<std::string>* extra_cpp1; 
    private: std::vector<std::string>* extra_build; 
    private: std::string file_name; 
    private: int errors_original_size; 
    private: stable_vector<token>* generated_tokens; 
    private: cpp2::parser parser; 
    private: std::string metafunction_name {}; 
    private: std::vector<std::string> metafunction_args {}; 
    private: bool metafunctions_used {false}; 

#line 47 "reflect.h2"
    public: compiler_services(

        cpp2::impl::in<std::vector<error_entry>*> errors_, 
        cpp2::impl::in<std::set<std::string>*> includes_, 
        cpp2::impl::in<std::vector<std::string>*> extra_cpp1_, 
        cpp2::impl::in<std::vector<std::string>*> extra_build_, 
        cpp2::impl::in<std::string> filename, 
        cpp2::impl::in<stable_vector<token>*> generated_tokens_
    );

#line 58 "reflect.h2"
    //  Common API
    //
    public: auto set_metafunction_name(cpp2::impl::in<std::string_view> name, cpp2::impl::in<std::vector<std::string>> args) & -> void;

#line 66 "reflect.h2"
    public: [[nodiscard]] auto get_metafunction_name() const& -> std::string_view;

    public: [[nodiscard]] auto get_argument(cpp2::impl::in<int> index) & -> std::string;

#line 76 "reflect.h2"
    public: [[nodiscard]] auto get_arguments() & -> std::vector<std::string>;

#line 81 "reflect.h2"
    public: [[nodiscard]] auto arguments_were_used() const& -> bool;
using parse_statement_ret = std::unique_ptr<statement_node>;


#line 83 "reflect.h2"
    protected: [[nodiscard]] auto parse_statement(

        std::string_view source
    ) & -> parse_statement_ret;

#line 136 "reflect.h2"
    public: [[nodiscard]] virtual auto position() const -> source_position;

#line 142 "reflect.h2"
    //  Error diagnosis and handling, integrated with compiler output
    //  Unlike a contract violation, .requires continues further processing
    //
    public: auto require(

        cpp2::impl::in<bool> b, 
        cpp2::impl::in<std::string_view> msg
    ) const& -> void;

#line 156 "reflect.h2"
    public: auto error(cpp2::impl::in<std::string_view> msg) const& -> void;

#line 165 "reflect.h2"
    //  Enable custom contracts on this object, integrated with compiler output
    //  Unlike .requires, a contract violation stops further processing
    //
    public: auto report_violation(auto const& msg) const& -> void;

#line 176 "reflect.h2"
    public: [[nodiscard]] auto is_active() const& -> auto;
    public: virtual ~compiler_services() noexcept;
public: compiler_services(compiler_services const& that);
public: compiler_services(compiler_services&& that) noexcept;

#line 177 "reflect.h2"
};

#line 180 "reflect.h2"
/*
//-----------------------------------------------------------------------
//
//  Type IDs
//
//-----------------------------------------------------------------------
//

//  All type_ids are wrappers around a pointer to node
//
type_id: @polymorphic_base @copyable type =
{
    this: compiler_services = ();

    n: type_id_node;

    protected operator=: (
        out this,
        n_: type_id_node,
        s : compiler_services
    )
    = {
        compiler_services = s;
        n = n_;
        assert( n, "a meta::type_id must point to a valid type_id_node, not null" );
    }

    is_wildcard         : (this) -> bool        = n.is_wildcard();
    is_pointer_qualified: (this) -> bool        = n.is_pointer_qualified();
    template_args_count : (this) -> int         = n.template_arguments().ssize();
    to_string           : (this) -> std::string = n.to_string();

    position: (override this) -> source_position = n.position();
}
*/

#line 217 "reflect.h2"
//-----------------------------------------------------------------------
//
//  Declarations
//
//-----------------------------------------------------------------------
//

//  All declarations are wrappers around a pointer to node
//
class declaration_base
: public compiler_services {

#line 230 "reflect.h2"
    protected: declaration_node* n; 

    protected: reflection_base(

        cpp2::impl::in<T*> n_, 
        cpp2::impl::in<compiler_services> s
    );

#line 243 "reflect.h2"
    public: [[nodiscard]] auto position() const -> source_position override;

    public: [[nodiscard]] auto print() const& -> std::string;
    public: virtual ~reflection_base() noexcept;
public: reflection_base(reflection_base const& that);
public: reflection_base(reflection_base&& that) noexcept;

#line 246 "reflect.h2"
};

#line 249 "reflect.h2"
//-----------------------------------------------------------------------
//  All declarations
//
class declaration
: public reflection_base<declaration_node> {

#line 256 "reflect.h2"
    public: explicit declaration(

        cpp2::impl::in<declaration_node*> n_, 
        cpp2::impl::in<compiler_services> s
    );

#line 265 "reflect.h2"
    public: [[nodiscard]] auto is_public() const& -> bool;
    public: [[nodiscard]] auto is_protected() const& -> bool;
    public: [[nodiscard]] auto is_private() const& -> bool;
    public: [[nodiscard]] auto is_default_access() const& -> bool;

    public: [[nodiscard]] auto default_to_public() & -> decltype(auto);
    public: [[nodiscard]] auto default_to_protected() & -> decltype(auto);
    public: [[nodiscard]] auto default_to_private() & -> decltype(auto);

    public: [[nodiscard]] auto make_public() & -> bool;
    public: [[nodiscard]] auto make_protected() & -> bool;
    public: [[nodiscard]] auto make_private() & -> bool;

    public: [[nodiscard]] auto has_name() const& -> bool;
    public: [[nodiscard]] auto has_name(cpp2::impl::in<std::string_view> s) const& -> bool;

    public: [[nodiscard]] auto name() const& -> std::string_view;

#line 286 "reflect.h2"
    public: [[nodiscard]] auto has_initializer() const& -> bool;

    public: [[nodiscard]] auto get_initializer() const& -> statement;

    public: [[nodiscard]] auto is_global() const& -> bool;
    public: [[nodiscard]] auto is_function() const& -> bool;
    public: [[nodiscard]] auto is_object() const& -> bool;
    public: [[nodiscard]] auto is_base_object() const& -> bool;
    public: [[nodiscard]] auto is_member_object() const& -> bool;
    public: [[nodiscard]] auto is_type() const& -> bool;
    public: [[nodiscard]] auto is_namespace() const& -> bool;
    public: [[nodiscard]] auto is_alias() const& -> bool;

    public: [[nodiscard]] auto is_type_alias() const& -> bool;
    public: [[nodiscard]] auto is_namespace_alias() const& -> bool;
    public: [[nodiscard]] auto is_object_alias() const& -> bool;

    public: [[nodiscard]] auto is_function_expression() const& -> bool;

    public: [[nodiscard]] auto as_function() const& -> function_declaration;
    public: [[nodiscard]] auto as_object() const& -> object_declaration;
    public: [[nodiscard]] auto as_type() const& -> type_declaration;
    public: [[nodiscard]] auto as_nonglobal_namespace() const& -> namespace_declaration;
    public: [[nodiscard]] auto as_alias() const& -> alias_declaration;

    public: [[nodiscard]] auto get_parent() const& -> declaration;

    public: [[nodiscard]] auto parent_is_function() const& -> bool;
    public: [[nodiscard]] auto parent_is_object() const& -> bool;
    public: [[nodiscard]] auto parent_is_type() const& -> bool;
    public: [[nodiscard]] auto parent_is_nonglobal_namespace() const& -> bool;
    public: [[nodiscard]] auto parent_is_alias() const& -> bool;

    public: [[nodiscard]] auto parent_is_type_alias() const& -> bool;
    public: [[nodiscard]] auto parent_is_namespace_alias() const& -> bool;
    public: [[nodiscard]] auto parent_is_object_alias() const& -> bool;

    public: [[nodiscard]] auto parent_is_polymorphic() const& -> bool;

    public: auto mark_for_removal_from_enclosing_type() & -> void;
    public: virtual ~declaration() noexcept;
public: declaration(declaration const& that);
public: declaration(declaration&& that) noexcept;


#line 328 "reflect.h2"
};

#line 331 "reflect.h2"
//-----------------------------------------------------------------------
//  Function declarations
//
class function_declaration
: public declaration {

#line 338 "reflect.h2"
    public: explicit function_declaration(

        cpp2::impl::in<declaration_node*> n_, 
        cpp2::impl::in<compiler_services> s
    );

#line 348 "reflect.h2"
    public: [[nodiscard]] auto index_of_parameter_named(cpp2::impl::in<std::string_view> s) const& -> int;
    public: [[nodiscard]] auto has_parameter_named(cpp2::impl::in<std::string_view> s) const& -> bool;
    public: [[nodiscard]] auto has_return_named(cpp2::impl::in<std::string_view> s) const& -> bool;
    public: [[nodiscard]] auto has_parameter_or_return_named(cpp2::impl::in<std::string_view> s) const& -> bool;
    public: [[nodiscard]] auto has_in_parameter_named(cpp2::impl::in<std::string_view> s) const& -> bool;
    public: [[nodiscard]] auto has_in_ref_parameter_named(cpp2::impl::in<std::string_view> s) const& -> bool;
    public: [[nodiscard]] auto has_copy_parameter_named(cpp2::impl::in<std::string_view> s) const& -> bool;
    public: [[nodiscard]] auto has_inout_parameter_named(cpp2::impl::in<std::string_view> s) const& -> bool;
    public: [[nodiscard]] auto has_out_parameter_named(cpp2::impl::in<std::string_view> s) const& -> bool;
    public: [[nodiscard]] auto has_move_parameter_named(cpp2::impl::in<std::string_view> s) const& -> bool;
    public: [[nodiscard]] auto has_forward_parameter_named(cpp2::impl::in<std::string_view> s) const& -> bool;
    public: [[nodiscard]] auto first_parameter_name() const& -> std::string;

    public: [[nodiscard]] auto has_parameter_with_name_and_pass(cpp2::impl::in<std::string_view> s, cpp2::impl::in<passing_style> pass) const& -> bool;

    public: [[nodiscard]] auto is_function_with_this() const& -> bool;
    public: [[nodiscard]] auto is_virtual() const& -> bool;
    public: [[nodiscard]] auto is_defaultable() const& -> bool;
    public: [[nodiscard]] auto is_constructor() const& -> bool;
    public: [[nodiscard]] auto is_default_constructor() const& -> bool;
    public: [[nodiscard]] auto is_move() const& -> bool;
    public: [[nodiscard]] auto is_swap() const& -> bool;
    public: [[nodiscard]] auto is_constructor_with_that() const& -> bool;
    public: [[nodiscard]] auto is_constructor_with_in_that() const& -> bool;
    public: [[nodiscard]] auto is_constructor_with_move_that() const& -> bool;
    public: [[nodiscard]] auto is_assignment() const& -> bool;
    public: [[nodiscard]] auto is_assignment_with_that() const& -> bool;
    public: [[nodiscard]] auto is_assignment_with_in_that() const& -> bool;
    public: [[nodiscard]] auto is_assignment_with_move_that() const& -> bool;
    public: [[nodiscard]] auto is_destructor() const& -> bool;

    public: [[nodiscard]] auto is_copy_or_move() const& -> bool;

    public: [[nodiscard]] auto has_declared_return_type() const& -> bool;
    public: [[nodiscard]] auto has_deduced_return_type() const& -> bool;
    public: [[nodiscard]] auto has_bool_return_type() const& -> bool;
    public: [[nodiscard]] auto has_non_void_return_type() const& -> bool;

    public: [[nodiscard]] auto has_compound_body() const& -> bool;

    public: [[nodiscard]] auto get_body() const& -> statement;
    public: [[nodiscard]] auto get_compound_body() const& -> compound_statement;
    public: [[nodiscard]] auto get_unnamed_return_type() const& -> std::string;
    public: [[nodiscard]] auto get_signature() const& -> std::string;

#line 395 "reflect.h2"
    public: [[nodiscard]] auto is_binary_comparison_function() const& -> bool;

    public: [[nodiscard]] auto get_parameters() const& -> std::vector<parameter_declaration>;

#line 401 "reflect.h2"
    public: [[nodiscard]] auto get_returns() const& -> std::vector<parameter_declaration>;

#line 413 "reflect.h2"
    public: [[nodiscard]] auto default_to_virtual() & -> decltype(auto);

    public: [[nodiscard]] auto make_virtual() & -> bool;

    public: auto add_initializer(cpp2::impl::in<std::string_view> source) & -> void;
    public: function_declaration(function_declaration const& that);
public: function_declaration(function_declaration&& that) noexcept;


#line 418 "reflect.h2"
};

#line 421 "reflect.h2"
//-----------------------------------------------------------------------
//  Object declarations
//
class object_declaration
: public declaration {

#line 428 "reflect.h2"
    public: explicit object_declaration(

        cpp2::impl::in<declaration_node*> n_, 
        cpp2::impl::in<compiler_services> s
    );

#line 438 "reflect.h2"
    public: [[nodiscard]] auto is_const() const& -> bool;
    public: [[nodiscard]] auto has_wildcard_type() const& -> bool;

    public: [[nodiscard]] auto type() const& -> std::string;

#line 448 "reflect.h2"
    public: [[nodiscard]] auto initializer() const& -> std::string;
    public: object_declaration(object_declaration const& that);
public: object_declaration(object_declaration&& that) noexcept;


#line 454 "reflect.h2"
};

#line 457 "reflect.h2"
//-----------------------------------------------------------------------
//  Type declarations
//
class type_declaration
: public declaration {

#line 464 "reflect.h2"
    public: explicit type_declaration(

#line 471 "reflect.h2"
class type_or_namespace_declaration
: public declaration {

#line 475 "reflect.h2"
    public: type_or_namespace_declaration(

        cpp2::impl::in<declaration_node*> n_, 
        cpp2::impl::in<compiler_services> s
    );

#line 474 "reflect.h2"
    public: auto reserve_names(cpp2::impl::in<std::string_view> name, auto&& ...etc) const& -> void;

#line 488 "reflect.h2"
    public: [[nodiscard]] auto is_polymorphic() const& -> bool;
    public: [[nodiscard]] auto is_final() const& -> bool;
    public: [[nodiscard]] auto make_final() & -> bool;

    public: [[nodiscard]] auto get_member_functions() const& -> std::vector<function_declaration>;

#line 503 "reflect.h2"
    public: [[nodiscard]] auto get_member_functions_needing_initializer() const& -> std::vector<function_declaration>;

#line 518 "reflect.h2"
    public: [[nodiscard]] auto get_member_objects() const& -> std::vector<object_declaration>;

#line 528 "reflect.h2"
    public: [[nodiscard]] auto get_member_types() const& -> std::vector<type_declaration>;

#line 538 "reflect.h2"
    public: [[nodiscard]] auto get_member_aliases() const& -> std::vector<alias_declaration>;

#line 548 "reflect.h2"
    public: [[nodiscard]] auto get_members() const& -> std::vector<declaration>;
struct query_declared_value_set_functions_ret { bool out_this_in_that; bool out_this_move_that; bool inout_this_in_that; bool inout_this_move_that; };



#line 558 "reflect.h2"
    public: [[nodiscard]] auto query_declared_value_set_functions() const& -> query_declared_value_set_functions_ret;

#line 573 "reflect.h2"
    public: auto add_member(cpp2::impl::in<std::string_view> source) & -> void;

#line 587 "reflect.h2"
    public: auto remove_marked_members() & -> void;
    public: auto remove_all_members() & -> void;

    public: auto disable_member_function_generation() & -> void;
    public: type_declaration(type_declaration const& that);
public: type_declaration(type_declaration&& that) noexcept;

#line 591 "reflect.h2"
};

#line 594 "reflect.h2"
//-----------------------------------------------------------------------
//  Alias declarations
//
class alias_declaration
: public declaration {

#line 601 "reflect.h2"
    public: explicit alias_declaration(

        cpp2::impl::in<declaration_node*> n_, 
        cpp2::impl::in<compiler_services> s
    );
    public: alias_declaration(alias_declaration const& that);
public: alias_declaration(alias_declaration&& that) noexcept;


#line 610 "reflect.h2"
};

#line 613 "reflect.h2"
//-----------------------------------------------------------------------
//
//  Metafunctions - these are hardwired for now until we get to the
//  step of writing a Cpp2 interpreter to run inside the compiler
//
//-----------------------------------------------------------------------
//

#line 667 "reflect.h2"
    public: parameter_declaration(

        cpp2::impl::in<parameter_declaration_node*> n_, 
        cpp2::impl::in<compiler_services> s
    );

#line 676 "reflect.h2"
    public: [[nodiscard]] auto get_declaration() const& -> object_declaration;
    public: [[nodiscard]] auto get_passing_style() const& -> passing_style;

    public: [[nodiscard]] auto is_implicit() const& -> bool;
    public: [[nodiscard]] auto is_virtual() const& -> bool;
    public: [[nodiscard]] auto is_override() const& -> bool;
    public: [[nodiscard]] auto is_final() const& -> bool;
    public: parameter_declaration(parameter_declaration const& that);
public: parameter_declaration(parameter_declaration&& that) noexcept;

#line 683 "reflect.h2"
};

#line 696 "reflect.h2"
using multiplicative_expression = binary_expression<"multiplicative",is_as_expression_node>;
using additive_expression = binary_expression<"additive",multiplicative_expression_node>;
using shift_expression = binary_expression<"shift",additive_expression_node>;
using compare_expression = binary_expression<"compare",shift_expression_node>;
using relational_expression = binary_expression<"relational",compare_expression_node>;
using equality_expression = binary_expression<"equality",relational_expression_node>;
using bit_and_expression = binary_expression<"bit-and",equality_expression_node>;
using bit_xor_expression = binary_expression<"bit-xor",bit_and_expression_node>;
using bit_or_expression = binary_expression<"bit-or",bit_xor_expression_node>;
using logical_and_expression = binary_expression<"logical-and",bit_or_expression_node>;
using logical_or_expression = binary_expression<"logical-or",logical_and_expression_node>;
using assignment_expression = binary_expression<"assignment",logical_or_expression_node>;

template<String Name, typename Term> class binary_expression
: public reflection_base<binary_expression_node<Name,Term>> {

#line 713 "reflect.h2"
    public: binary_expression(

        binary_expression_node<Name,Term>* const& n_, 
        cpp2::impl::in<compiler_services> s
    );

#line 722 "reflect.h2"
    public: [[nodiscard]] auto is_fold_expression() const& -> bool;
    public: [[nodiscard]] auto lhs_is_id_expression() const& -> bool;
    public: [[nodiscard]] auto is_standalone_expression() const& -> bool;
    public: [[nodiscard]] auto terms_size() const& -> int;
    public: [[nodiscard]] auto is_identifier() const& -> bool;
    public: [[nodiscard]] auto is_id_expression() const& -> bool;
    public: [[nodiscard]] auto is_unqualified_id() const& -> bool;
    public: [[nodiscard]] auto is_expression_list() const& -> bool;
    public: [[nodiscard]] auto is_literal() const& -> bool;

    public: template<typename T> class term_t {
        private: std::string op; 
        private: T term; 

        public: term_t(auto&& o, auto&& ptr, auto&& cs);

        public: [[nodiscard]] auto get_op() const& -> std::string;
        public: [[nodiscard]] auto get_term() const& -> T;
        public: term_t(term_t const& that);

public: auto operator=(term_t const& that) -> term_t& ;
public: term_t(term_t&& that) noexcept;
public: auto operator=(term_t&& that) noexcept -> term_t& ;

#line 740 "reflect.h2"
    };

    public: [[nodiscard]] auto get_terms() const& -> auto;

#line 817 "reflect.h2"
    public: [[nodiscard]] auto as_expression_list() const& -> expression_list;
    public: [[nodiscard]] auto as_literal() const& -> std::string;

#line 821 "reflect.h2"
    public: [[nodiscard]] auto get_if_only_a_postfix_expression() const& -> postfix_expression;

    public: [[nodiscard]] auto get_lhs_postfix_expression() const& -> postfix_expression;

    public: [[nodiscard]] auto get_second_postfix_expression() const& -> postfix_expression;

    public: [[nodiscard]] auto is_result_a_temporary_variable() const& -> bool;

    public: [[nodiscard]] auto to_string() const& -> std::string;
    public: binary_expression(binary_expression const& that);
public: binary_expression(binary_expression&& that) noexcept;

#line 830 "reflect.h2"
};

#line 836 "reflect.h2"
class expression_list
: public reflection_base<expression_list_node> {

#line 840 "reflect.h2"
    public: expression_list(

        cpp2::impl::in<expression_list_node*> n_, 
        cpp2::impl::in<compiler_services> s
    );

#line 849 "reflect.h2"
    public: [[nodiscard]] auto is_empty() const& -> bool;
    public: [[nodiscard]] auto is_fold_expression() const& -> bool;

    public: [[nodiscard]] auto get_expressions() const& -> std::vector<expression>;

#line 862 "reflect.h2"
    public: [[nodiscard]] auto to_string() const& -> std::string;
    public: expression_list(expression_list const& that);
public: expression_list(expression_list&& that) noexcept;

#line 863 "reflect.h2"
};

#line 869 "reflect.h2"
class prefix_expression
: public reflection_base<prefix_expression_node> {

#line 873 "reflect.h2"
    public: prefix_expression(

        cpp2::impl::in<prefix_expression_node*> n_, 
        cpp2::impl::in<compiler_services> s
    );

#line 882 "reflect.h2"
    public: [[nodiscard]] auto get_ops() const& -> std::vector<std::string>;

#line 890 "reflect.h2"
    public: [[nodiscard]] auto get_postfix_expression() const& -> postfix_expression;

    public: [[nodiscard]] auto is_fold_expression() const& -> bool;
    public: [[nodiscard]] auto is_identifier() const& -> bool;
    public: [[nodiscard]] auto is_id_expression() const& -> bool;
    public: [[nodiscard]] auto is_unqualified_id() const& -> bool;
    public: [[nodiscard]] auto is_expression_list() const& -> bool;
    public: [[nodiscard]] auto is_literal() const& -> bool;
    public: [[nodiscard]] auto is_result_a_temporary_variable() const& -> bool;

    public: [[nodiscard]] auto as_expression_list() const& -> expression_list;
    public: [[nodiscard]] auto as_literal() const& -> std::string;
    public: [[nodiscard]] auto as_identifier() const& -> std::string;

    public: [[nodiscard]] auto to_string() const& -> std::string;
    public: virtual ~prefix_expression() noexcept;
public: prefix_expression(prefix_expression const& that);
public: prefix_expression(prefix_expression&& that) noexcept;

#line 905 "reflect.h2"
};

#line 911 "reflect.h2"
class postfix_expression
: public reflection_base<postfix_expression_node> {

#line 915 "reflect.h2"
    public: postfix_expression(

        cpp2::impl::in<postfix_expression_node*> n_, 
        cpp2::impl::in<compiler_services> s
    );

#line 924 "reflect.h2"
    public: [[nodiscard]] auto get_primary_expression() const& -> primary_expression;

    public: class term_t {
        private: postfix_expression_node::term const* term_; 
        private: compiler_services const* cs_; 

        public: term_t(auto&& term, auto&& cs);

        public: [[nodiscard]] auto get_op() const& -> std::string_view;

#line 940 "reflect.h2"
        public: [[nodiscard]] auto is_id_expression() const& -> bool;
        public: [[nodiscard]] auto is_expression_list() const& -> bool;
        public: [[nodiscard]] auto is_expression() const& -> bool;

        public: [[nodiscard]] auto get_id_expression() const& -> id_expression;
        public: [[nodiscard]] auto get_expression_list() const& -> expression_list;
        public: [[nodiscard]] auto get_expression() const& -> expression;
        public: term_t(term_t const& that);
public: term_t(term_t&& that) noexcept;

#line 947 "reflect.h2"
    };

    public: [[nodiscard]] auto get_terms() const& -> auto;

#line 955 "reflect.h2"
    public: [[nodiscard]] auto is_fold_expression() const& -> bool;
    public: [[nodiscard]] auto is_identifier() const& -> bool;
    public: [[nodiscard]] auto is_id_expression() const& -> bool;
    public: [[nodiscard]] auto is_unqualified_id() const& -> bool;
    public: [[nodiscard]] auto is_expression_list() const& -> bool;
    public: [[nodiscard]] auto is_literal() const& -> bool;

    public: [[nodiscard]] auto as_identifier() const& -> std::string;
    public: [[nodiscard]] auto as_expression_list() const& -> expression_list;
    public: [[nodiscard]] auto as_literal() const& -> std::string;

    public: [[nodiscard]] auto get_first_token_ignoring_this() const& -> std::string_view;

#line 972 "reflect.h2"
    public: [[nodiscard]] auto starts_with_function_call_with_num_parameters(cpp2::impl::in<int> num) const& -> bool;
    public: [[nodiscard]] auto is_result_a_temporary_variable() const& -> bool;

    public: [[nodiscard]] auto to_string() const& -> std::string;
    public: postfix_expression(postfix_expression const& that);
public: postfix_expression(postfix_expression&& that) noexcept;

#line 976 "reflect.h2"
};

#line 982 "reflect.h2"
class template_arg
: public reflection_base<template_argument> {

#line 986 "reflect.h2"
    public: template_arg(

        cpp2::impl::in<template_argument*> n_, 
        cpp2::impl::in<compiler_services> s
    );

#line 995 "reflect.h2"
    public: [[nodiscard]] auto is_expression() const& -> bool;
    public: [[nodiscard]] auto is_type_id() const& -> bool;

    public: [[nodiscard]] auto as_expression() const& -> expression;
    public: [[nodiscard]] auto as_type_id() const& -> type_id;

    public: [[nodiscard]] auto to_string() const& -> std::string;
    public: template_arg(template_arg const& that);
public: template_arg(template_arg&& that) noexcept;

#line 1002 "reflect.h2"
};

#line 1008 "reflect.h2"
class unqualified_id
: public reflection_base<unqualified_id_node> {

#line 1012 "reflect.h2"
    public: unqualified_id(

        cpp2::impl::in<unqualified_id_node*> n_, 
        cpp2::impl::in<compiler_services> s
    );

#line 1021 "reflect.h2"
    public: [[nodiscard]] auto is_identifier() const& -> bool;

    public: [[nodiscard]] auto get_identifier() const& -> std::string;

#line 1031 "reflect.h2"
    public: [[nodiscard]] auto as_token() const& -> std::string;

    public: [[nodiscard]] auto to_string() const& -> std::string;
    public: unqualified_id(unqualified_id const& that);
public: unqualified_id(unqualified_id&& that) noexcept;

#line 1034 "reflect.h2"
};

#line 1040 "reflect.h2"
class qualified_id
: public reflection_base<qualified_id_node> {

#line 1044 "reflect.h2"
    public: qualified_id(

        cpp2::impl::in<qualified_id_node*> n_, 
        cpp2::impl::in<compiler_services> s
    );

#line 1053 "reflect.h2"
    public: class term_t {
        private: std::string op; 
        private: unqualified_id unqualified; 

        public: term_t(auto&& o, auto&& ptr, auto&& cs);

        public: [[nodiscard]] auto get_op() const& -> std::string;
        public: [[nodiscard]] auto get_unqualified() const& -> unqualified_id;
        public: term_t(term_t const& that);
public: term_t(term_t&& that) noexcept;

#line 1061 "reflect.h2"
    };

    public: [[nodiscard]] auto get_terms() const& -> auto;

#line 1075 "reflect.h2"
    public: [[nodiscard]] auto as_token() const& -> std::string;

    public: [[nodiscard]] auto to_string() const& -> std::string;
    public: qualified_id(qualified_id const& that);
public: qualified_id(qualified_id&& that) noexcept;

#line 1078 "reflect.h2"
};

#line 1084 "reflect.h2"
class type_id
: public reflection_base<type_id_node> {

#line 1088 "reflect.h2"
    public: type_id(

        cpp2::impl::in<type_id_node*> n_, 
        cpp2::impl::in<compiler_services> s
    );

#line 1103 "reflect.h2"
    public: [[nodiscard]] auto is_postfix_expression() const& -> bool;
    public: [[nodiscard]] auto is_qualified_id() const& -> bool;
    public: [[nodiscard]] auto is_unqualified_id() const& -> bool;
    public: [[nodiscard]] auto is_function_typeid() const& -> bool;
    public: [[nodiscard]] auto is_keyword() const& -> bool;
    public: [[nodiscard]] auto is_wildcard() const& -> bool;
    public: [[nodiscard]] auto is_pointer_qualified() const& -> bool;
    public: [[nodiscard]] auto is_concept() const& -> bool;

    public: [[nodiscard]] auto as_postfix_expression() const& -> postfix_expression;
    public: [[nodiscard]] auto as_qualified_id() const& -> qualified_id;
    public: [[nodiscard]] auto as_unqualified_id() const& -> unqualified_id;

#line 1117 "reflect.h2"
    public: [[nodiscard]] auto as_keyword() const& -> std::string;
    public: [[nodiscard]] auto as_token() const& -> std::string;

    public: [[nodiscard]] auto to_string() const& -> std::string;
    public: type_id(type_id const& that);
public: type_id(type_id&& that) noexcept;

#line 1121 "reflect.h2"
};

#line 1127 "reflect.h2"
class primary_expression
: public reflection_base<primary_expression_node> {

#line 1131 "reflect.h2"
    public: primary_expression(

        cpp2::impl::in<primary_expression_node*> n_, 
        cpp2::impl::in<compiler_services> s
    );

#line 1146 "reflect.h2"
    public: [[nodiscard]] auto is_fold_expression() const& -> bool;
    public: [[nodiscard]] auto is_identifier() const& -> bool;
    public: [[nodiscard]] auto is_id_expression() const& -> bool;
    public: [[nodiscard]] auto is_unqualified_id() const& -> bool;
    public: [[nodiscard]] auto is_expression_list() const& -> bool;
    public: [[nodiscard]] auto is_literal() const& -> bool;
    public: [[nodiscard]] auto is_declaration() const& -> bool;

    public: [[nodiscard]] auto as_identifier() const& -> std::string;
    public: [[nodiscard]] auto as_expression_list() const& -> expression_list;
    public: [[nodiscard]] auto as_literal() const& -> std::string;
    public: [[nodiscard]] auto as_declaration() const& -> declaration;

    public: [[nodiscard]] auto to_string() const& -> std::string;
    public: primary_expression(primary_expression const& that);
public: primary_expression(primary_expression&& that) noexcept;

#line 1160 "reflect.h2"
};

#line 1166 "reflect.h2"
class id_expression
: public reflection_base<id_expression_node> {

#line 1170 "reflect.h2"
    public: id_expression(

        cpp2::impl::in<id_expression_node*> n_, 
        cpp2::impl::in<compiler_services> s
    );

#line 1185 "reflect.h2"
    public: [[nodiscard]] auto is_fold_expression() const& -> bool;
    public: [[nodiscard]] auto is_empty() const& -> bool;
    public: [[nodiscard]] auto is_identifier() const& -> bool;
    public: [[nodiscard]] auto is_qualified() const& -> bool;
    public: [[nodiscard]] auto is_unqualified() const& -> bool;

    public: [[nodiscard]] auto as_identifier() const& -> std::string;
    public: [[nodiscard]] auto as_qualified() const& -> qualified_id;
    public: [[nodiscard]] auto as_unqualified() const& -> unqualified_id;

    public: [[nodiscard]] auto to_string() const& -> std::string;
    public: virtual ~id_expression() noexcept;
public: id_expression(id_expression const& that);
public: id_expression(id_expression&& that) noexcept;

#line 1196 "reflect.h2"
};

#line 1202 "reflect.h2"
class expression
: public reflection_base<expression_node> {

#line 1206 "reflect.h2"
    public: expression(

        cpp2::impl::in<expression_node*> n_, 
        cpp2::impl::in<compiler_services> s
    );

#line 1215 "reflect.h2"
    public: [[nodiscard]] auto is_fold_expression() const& -> bool;
    public: [[nodiscard]] auto is_standalone_expression() const& -> bool;
    public: [[nodiscard]] auto subexpression_count() const& -> int;
    public: [[nodiscard]] auto is_identifier() const& -> bool;
    public: [[nodiscard]] auto is_id_expression() const& -> bool;
    public: [[nodiscard]] auto is_unqualified_id() const& -> bool;
    public: [[nodiscard]] auto is_expression_list() const& -> bool;
    public: [[nodiscard]] auto is_empty_expression_list() const& -> bool;
    public: [[nodiscard]] auto is_literal() const& -> bool;
    public: [[nodiscard]] auto is_assignment_expression() const& -> bool;

    public: [[nodiscard]] auto is_simple_assignment() const& -> bool;
struct get_lhs_rhs_if_simple_assignment_ret { postfix_expression lhs; logical_or_expression rhs; };



#line 1231 "reflect.h2"
    public: [[nodiscard]] auto get_lhs_rhs_if_simple_assignment() const& -> get_lhs_rhs_if_simple_assignment_ret;

#line 1242 "reflect.h2"
    public: [[nodiscard]] auto as_assignment_expression() const& -> assignment_expression;
    public: [[nodiscard]] auto as_expression_list() const& -> expression_list;
    public: [[nodiscard]] auto as_literal() const& -> std::string;

    public: [[nodiscard]] auto to_string() const& -> std::string;
    public: virtual ~expression() noexcept;
public: expression(expression const& that);
public: expression(expression&& that) noexcept;

#line 1247 "reflect.h2"
};

#line 1253 "reflect.h2"
class is_as_expression
: public reflection_base<is_as_expression_node> {

#line 1257 "reflect.h2"
    public: is_as_expression(

        cpp2::impl::in<is_as_expression_node*> n_, 
        cpp2::impl::in<compiler_services> s
    );

#line 1266 "reflect.h2"
    public: class term_t {
        private: std::string op; 
        private: expression expr; 

        public: term_t(auto&& o, auto&& ptr, auto&& cs);

        public: [[nodiscard]] auto get_op() const& -> std::string;
        public: [[nodiscard]] auto get_expr() const& -> expression;
        public: term_t(term_t const& that);
public: term_t(term_t&& that) noexcept;

#line 1274 "reflect.h2"
    };

    public: [[nodiscard]] auto get_expression() const& -> prefix_expression;

    public: [[nodiscard]] auto get_terms() const& -> auto;

#line 1284 "reflect.h2"
    public: [[nodiscard]] auto is_fold_expression() const& -> bool;
    public: [[nodiscard]] auto is_identifier() const& -> bool;
    public: [[nodiscard]] auto is_id_expression() const& -> bool;
    public: [[nodiscard]] auto is_unqualified_id() const& -> bool;
    public: [[nodiscard]] auto is_expression_list() const& -> bool;
    public: [[nodiscard]] auto is_literal() const& -> bool;

    public: [[nodiscard]] auto as_expression_list() const& -> expression_list;
    public: [[nodiscard]] auto as_literal() const& -> std::string;

    public: [[nodiscard]] auto get_identifier() const& -> std::string_view;

#line 1300 "reflect.h2"
    public: [[nodiscard]] auto to_string() const& -> std::string;
    public: virtual ~is_as_expression() noexcept;
public: is_as_expression(is_as_expression const& that);
public: is_as_expression(is_as_expression&& that) noexcept;

#line 1301 "reflect.h2"
};

#line 1314 "reflect.h2"
class statement
: public reflection_base<statement_node> {

#line 1318 "reflect.h2"
    public: statement(

        cpp2::impl::in<statement_node*> n_, 
        cpp2::impl::in<compiler_services> s
    );

#line 1327 "reflect.h2"
    public: [[nodiscard]] auto get_parameters() const& -> std::vector<parameter_declaration>;

#line 1337 "reflect.h2"
    public: [[nodiscard]] auto is_expression_statement() const& -> bool;
    public: [[nodiscard]] auto is_compound_statement() const& -> bool;
    public: [[nodiscard]] auto is_selection_statement() const& -> bool;
    public: [[nodiscard]] auto is_declaration() const& -> bool;
    public: [[nodiscard]] auto is_return_statement() const& -> bool;
    public: [[nodiscard]] auto is_iteration_statement() const& -> bool;
    public: [[nodiscard]] auto is_using_statement() const& -> bool;
    public: [[nodiscard]] auto is_contract() const& -> bool;
    public: [[nodiscard]] auto is_inspect_expression() const& -> bool;
    public: [[nodiscard]] auto is_jump_statement() const& -> bool;

    public: [[nodiscard]] auto as_expression_statement() const& -> expression_statement;
    public: [[nodiscard]] auto as_compound_statement() const& -> compound_statement;
    public: [[nodiscard]] auto as_selection_statement() const& -> selection_statement;
    public: [[nodiscard]] auto as_declaration() const& -> declaration;
    public: [[nodiscard]] auto as_return_statement() const& -> return_statement;
    public: [[nodiscard]] auto as_iteration_statement() const& -> iteration_statement;

#line 1359 "reflect.h2"
    public: [[nodiscard]] auto to_string() const& -> std::string;
    public: virtual ~statement() noexcept;
public: statement(statement const& that);
public: statement(statement&& that) noexcept;

#line 1360 "reflect.h2"
};

#line 1366 "reflect.h2"
class expression_statement
: public reflection_base<expression_statement_node> {

#line 1370 "reflect.h2"
    public: expression_statement(

        cpp2::impl::in<expression_statement_node*> n_, 
        cpp2::impl::in<compiler_services> s
    );

#line 1379 "reflect.h2"
    public: [[nodiscard]] auto get_expression() const& -> expression;

    public: [[nodiscard]] auto to_string() const& -> std::string;
    public: expression_statement(expression_statement const& that);
public: expression_statement(expression_statement&& that) noexcept;

#line 1382 "reflect.h2"
};

#line 1388 "reflect.h2"
class compound_statement
: public reflection_base<compound_statement_node> {

#line 1392 "reflect.h2"
    public: compound_statement(

        cpp2::impl::in<compound_statement_node*> n_, 
        cpp2::impl::in<compiler_services> s
    );

#line 1401 "reflect.h2"
    public: [[nodiscard]] auto get_statements() const& -> std::vector<statement>;

#line 1411 "reflect.h2"
    public: auto add_statement(cpp2::impl::in<std::string_view> source, cpp2::impl::in<int> before_position = 0) & -> void;
    public: compound_statement(compound_statement const& that);
public: compound_statement(compound_statement&& that) noexcept;


#line 1421 "reflect.h2"
};

#line 1427 "reflect.h2"
class selection_statement
: public reflection_base<selection_statement_node> {

#line 1431 "reflect.h2"
    public: selection_statement(

        cpp2::impl::in<selection_statement_node*> n_, 
        cpp2::impl::in<compiler_services> s
    );

#line 1440 "reflect.h2"
    public: [[nodiscard]] auto has_false_branch_in_source_code() const& -> bool;
    public: [[nodiscard]] auto has_false_branch() const& -> bool;

    public: [[nodiscard]] auto get_identifier() const& -> std::string_view;
    public: [[nodiscard]] auto get_expression() const& -> logical_or_expression;
    public: [[nodiscard]] auto get_true_branch() const& -> compound_statement;
    public: [[nodiscard]] auto get_false_branch() const& -> compound_statement;
    public: selection_statement(selection_statement const& that);
public: selection_statement(selection_statement&& that) noexcept;

#line 1447 "reflect.h2"
};

#line 1453 "reflect.h2"
class return_statement
: public reflection_base<return_statement_node> {

#line 1457 "reflect.h2"
    public: return_statement(

        cpp2::impl::in<return_statement_node*> n_, 
        cpp2::impl::in<compiler_services> s
    );

#line 1466 "reflect.h2"
    public: [[nodiscard]] auto has_expression() const& -> bool;

    public: [[nodiscard]] auto get_expression() const& -> expression;
    public: return_statement(return_statement const& that);
public: return_statement(return_statement&& that) noexcept;

#line 1469 "reflect.h2"
};

#line 1475 "reflect.h2"
class iteration_statement
: public reflection_base<iteration_statement_node> {

#line 1479 "reflect.h2"
    public: iteration_statement(

        cpp2::impl::in<iteration_statement_node*> n_, 
        cpp2::impl::in<compiler_services> s
    );

#line 1488 "reflect.h2"
    public: [[nodiscard]] auto is_do() const& -> bool;
    public: [[nodiscard]] auto is_while() const& -> bool;
    public: [[nodiscard]] auto is_for() const& -> bool;
    public: [[nodiscard]] auto has_next() const& -> bool;

    public: [[nodiscard]] auto get_label() const& -> std::string;
    public: [[nodiscard]] auto get_next_expression() const& -> assignment_expression;
    public: [[nodiscard]] auto get_do_while_condition() const& -> logical_or_expression;
    public: [[nodiscard]] auto get_do_while_body() const& -> compound_statement;
    public: [[nodiscard]] auto get_for_range() const& -> expression;
    public: [[nodiscard]] auto get_for_parameter() const& -> parameter_declaration;
    public: [[nodiscard]] auto get_for_body() const& -> statement;
    public: iteration_statement(iteration_statement const& that);
public: iteration_statement(iteration_statement&& that) noexcept;

#line 1500 "reflect.h2"
};

#line 1515 "reflect.h2"
auto add_virtual_destructor(meta::type_declaration& t) -> void;

#line 631 "reflect.h2"
//-----------------------------------------------------------------------
//
//      "... an abstract base class defines an interface ..."
//
//          -- Stroustrup (The Design and Evolution of C++, 12.3.1)
//
//-----------------------------------------------------------------------
//
//  interface
//
//  an abstract base class having only pure virtual functions
//
auto interface(meta::type_declaration& t) -> void;

#line 670 "reflect.h2"
//-----------------------------------------------------------------------
//
//     "C.35: A base class destructor should be either public and
//      virtual, or protected and non-virtual."
//
//     "[C.43] ... a base class should not be copyable, and so does not
//      necessarily need a default constructor."
//
//          -- Stroustrup, Sutter, et al. (C++ Core Guidelines)
//
//-----------------------------------------------------------------------
//
//  polymorphic_base
//
//  A pure polymorphic base type that is not copyable, and whose
//  destructor is either public and virtual or protected and nonvirtual.
//
//  Unlike an interface, it can have nonpublic and nonvirtual functions.
//
auto polymorphic_base(meta::type_declaration& t) -> void;

#line 714 "reflect.h2"
//-----------------------------------------------------------------------
//
//     "... A totally ordered type ... requires operator<=> that
//      returns std::strong_ordering. If the function is not
//      user-written, a lexicographical memberwise implementation
//      is generated by default..."
//
//          -- P0707R4, section 3
//
//      Note: This feature derived from Cpp2 was already adopted
//            into Standard C++ via paper P0515, so most of the
//            heavy lifting is done by the Cpp1 C++20/23 compiler,
//            including the memberwise default semantics
//            (In contrast, cppfront has to do the work itself for
//            default memberwise semantics for operator= assignment
//            as those aren't yet part of Standard C++)
//
//-----------------------------------------------------------------------
//

auto ordered_impl(
    meta::type_declaration& t, 
    cpp2::impl::in<std::string_view> ordering
) -> void;

#line 758 "reflect.h2"
//-----------------------------------------------------------------------
//  ordered - a totally ordered type
//
//  Note: the ordering that should be encouraged as default gets the nice name
//
auto ordered(meta::type_declaration& t) -> void;

#line 768 "reflect.h2"
//-----------------------------------------------------------------------
//  weakly_ordered - a weakly ordered type
//
auto weakly_ordered(meta::type_declaration& t) -> void;

#line 776 "reflect.h2"
//-----------------------------------------------------------------------
//  partially_ordered - a partially ordered type
//
auto partially_ordered(meta::type_declaration& t) -> void;

#line 785 "reflect.h2"
//-----------------------------------------------------------------------
//
//     "A value is ... a regular type. It must have all public
//      default construction, copy/move construction/assignment,
//      and destruction, all of which are generated by default
//      if not user-written; and it must not have any protected
//      or virtual functions (including the destructor)."
//
//          -- P0707R4, section 3
//
//-----------------------------------------------------------------------
//
//  copyable
//
//  A type with (copy and move) x (construction and assignment)
//
auto copyable(meta::type_declaration& t) -> void;

#line 828 "reflect.h2"
//-----------------------------------------------------------------------
//
//  basic_value
//
//  A regular type: copyable, plus has public default construction
//  and no protected or virtual functions
//
auto basic_value(meta::type_declaration& t) -> void;

#line 853 "reflect.h2"
//-----------------------------------------------------------------------
//
//     "A 'value' is a totally ordered basic_value..."
//
//          -- P0707R4, section 3
//
//  value - a value type that is totally ordered
//
//  Note: the ordering that should be encouraged as default gets the nice name
//
auto value(meta::type_declaration& t) -> void;

#line 869 "reflect.h2"
auto weakly_ordered_value(meta::type_declaration& t) -> void;

#line 875 "reflect.h2"
auto partially_ordered_value(meta::type_declaration& t) -> void;

#line 882 "reflect.h2"
//-----------------------------------------------------------------------
//
//     C.20: If you can avoid defining default operations, do
//
//     ##### Reason
//
//     It's the simplest and gives the cleanest semantics.
//
//     ...
//
//     This is known as "the rule of zero".
//
//          -- C++ Core Guidelines
//             C.20: If you can avoid defining any default operations, do
//             <https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#Rc-zero>
//
//-----------------------------------------------------------------------
//
//  cpp1_rule_of_zero
//
//  a type without declared copy/move/destructor functions
//
auto cpp1_rule_of_zero(meta::type_declaration& t) -> void;

#line 916 "reflect.h2"
//-----------------------------------------------------------------------
//
//     "By definition, a `struct` is a `class` in which members
//      are by default `public`; that is,
//
//      	struct s { ...
//
//      is simply shorthand for
//
//          class s { public: ...
//
//      ... Which style you use depends on circumstances and taste.
//      I usually prefer to use `struct` for classes that have all
//      data `public`."
//
//          -- Stroustrup (The C++ Programming Language, 3rd ed., p. 234)
//
//-----------------------------------------------------------------------
//
//  struct
//
//  a type with only public bases, objects, and functions,
//  no virtual functions, and no user-defined constructors
//  (i.e., no invariants) or assignment or destructors.
//
auto cpp2_struct(meta::type_declaration& t) -> void;

#line 988 "reflect.h2"
//-----------------------------------------------------------------------
//
//     "C enumerations constitute a curiously half-baked concept. ...
//      the cleanest way out was to deem each enumeration a separate type."
//
//          -- Stroustrup (The Design and Evolution of C++, 11.7)
//
//     "An enumeration is a distinct type ... with named constants"
//
//          -- ISO C++ Standard
//
//-----------------------------------------------------------------------
//
//  basic_enum
//
//  a type together with named constants that are its possible values
//
class value_member_info {
    public: std::string name; 
    public: std::string type; 
    public: std::string value; 
    public: value_member_info(auto const& name_, auto const& type_, auto const& value_);

#line 1009 "reflect.h2"
};

auto basic_enum(
    meta::type_declaration& t, 
    auto const& nextval, 
    cpp2::impl::in<bool> bitwise
    ) -> void;

#line 1206 "reflect.h2"
//-----------------------------------------------------------------------
//
//    "An enum[...] is a totally ordered value type that stores a
//     value of its enumerators's type, and otherwise has only public
//     member variables of its enumerator's type, all of which are
//     naturally scoped because they are members of a type."
//
//          -- P0707R4, section 3
//
auto cpp2_enum(meta::type_declaration& t) -> void;

#line 1232 "reflect.h2"
//-----------------------------------------------------------------------
//
//     "flag_enum expresses an enumeration that stores values
//      corresponding to bitwise-or'd enumerators. The enumerators must
//      be powers of two, and are automatically generated [...] A none
//      value is provided [...] Operators | and & are provided to
//      combine and extract values."
//
//          -- P0707R4, section 3
//
auto flag_enum(meta::type_declaration& t) -> void;

#line 1264 "reflect.h2"
//-----------------------------------------------------------------------
//
//     "As with void*, programmers should know that unions [...] are
//      inherently dangerous, should be avoided wherever possible,
//      and should be handled with special care when actually needed."
//
//          -- Stroustrup (The Design and Evolution of C++, 14.3.4.1)
//
//     "C++17 needs a type-safe union... The implications of the
//      consensus `variant` design are well understood and have been
//      explored over several LEWG discussions, over a thousand emails,
//      a joint LEWG/EWG session, and not to mention 12 years of
//      experience with Boost and other libraries."
//
//          -- Axel Naumann, in P0088 (wg21.link/p0088),
//             the adopted proposal for C++17 std::variant
//
//-----------------------------------------------------------------------
//
//  union
//
//  a type that contains exactly one of a fixed set of values at a time
//

auto cpp2_union(meta::type_declaration& t) -> void;

#line 1435 "reflect.h2"
//-----------------------------------------------------------------------
//
//  print - output a pretty-printed visualization of t
//
auto print(cpp2::impl::in<meta::type_declaration> t) -> void;

#line 1445 "reflect.h2"
//-----------------------------------------------------------------------
//
//  apply_metafunctions
//
[[nodiscard]] auto apply_metafunctions(
    declaration_node& n, 
    type_declaration& rtype, 
    auto const& error
    ) -> bool;

#line 1561 "reflect.h2"
}

}


//=== Cpp2 function definitions =================================================

#line 1 "reflect.h2"

#line 20 "reflect.h2"
namespace cpp2 {

namespace meta {

#line 46 "reflect.h2"
    compiler_services::compiler_services(

        cpp2::impl::in<std::vector<error_entry>*> errors_, 
        cpp2::impl::in<std::set<std::string>*> includes_, 
        cpp2::impl::in<std::vector<std::string>*> extra_cpp1_, 
        cpp2::impl::in<std::vector<std::string>*> extra_build_, 
        cpp2::impl::in<std::string> filename, 
        cpp2::impl::in<stable_vector<token>*> generated_tokens_
    )
        : errors{ errors_ }
        , includes{ includes_ }
        , extra_cpp1{ extra_cpp1_ }
        , extra_build{ extra_build_ }
        , file_name{ filename }
        , errors_original_size{ cpp2::unchecked_narrow<int>(std::ssize(*cpp2::impl::assert_not_null(errors))) }
        , generated_tokens{ generated_tokens_ }
        , parser{ *cpp2::impl::assert_not_null(errors) }
#line 51 "reflect.h2"
    {

#line 56 "reflect.h2"
    }

#line 60 "reflect.h2"
    auto compiler_services::set_metafunction_name(cpp2::impl::in<std::string_view> name, cpp2::impl::in<std::vector<std::string>> args) & -> void{
        metafunction_name  = name;
        metafunction_args  = args;
        metafunctions_used = CPP2_UFCS_0(empty, args);
    }

#line 66 "reflect.h2"
    [[nodiscard]] auto compiler_services::get_metafunction_name() const& -> std::string_view { return metafunction_name;  }

#line 68 "reflect.h2"
    [[nodiscard]] auto compiler_services::get_argument(cpp2::impl::in<int> index) & -> std::string{
        metafunctions_used = true;
        if (([_0 = 0, _1 = index, _2 = CPP2_UFCS_0(ssize, metafunction_args)]{ return cpp2::cmp_less_eq(_0,_1) && cpp2::cmp_less(_1,_2); }())) {
            return CPP2_ASSERT_IN_BOUNDS(metafunction_args, index); 
        }
        return ""; 
    }

#line 76 "reflect.h2"
    [[nodiscard]] auto compiler_services::get_arguments() & -> std::vector<std::string>{
        metafunctions_used = true;
        return metafunction_args; 
    }

#line 81 "reflect.h2"
    [[nodiscard]] auto compiler_services::arguments_were_used() const& -> bool { return metafunctions_used;  }

#line 83 "reflect.h2"
    [[nodiscard]] auto compiler_services::parse_statement(

        std::string_view source
    ) & -> parse_statement_ret

    {
        CPP2_UFCS(push_back, generated_lines, std::vector<source_line>());
        auto lines {&CPP2_UFCS_0(back, generated_lines)}; 

        auto add_line {[&, _1 = lines](cpp2::in<std::string_view> s) mutable -> void{
            static_cast<void>(CPP2_UFCS(emplace_back, (*cpp2::assert_not_null(_1)), s, source_line::category::cpp2));
        }}; 
{
auto newline_pos = CPP2_UFCS(find, source, '\n');

        //  First split this string into source_lines
        //

#line 88 "reflect.h2"
        if ( cpp2::cmp_greater(CPP2_UFCS_0(ssize, source),1) 
            && newline_pos != source.npos) 
        {
            while( newline_pos != source.npos ) 
            {
                add_line(CPP2_UFCS(substr, source, 0, newline_pos));
                CPP2_UFCS(remove_prefix, source, newline_pos + 1);
                newline_pos = CPP2_UFCS(find, source, '\n');
            }
        }
}

#line 99 "reflect.h2"
        if (!(CPP2_UFCS_0(empty, source))) {
            std::move(add_line)(std::move(source));
        }

        //  Now lex this source fragment to generate
        //  a single grammar_map entry, whose .second
        //  is the vector of tokens
        static_cast<void>(CPP2_UFCS(emplace_back, generated_lexers, *cpp2::assert_not_null(errors)));
        auto tokens {&CPP2_UFCS_0(back, generated_lexers)}; 
        CPP2_UFCS(lex, (*cpp2::assert_not_null(tokens)), *cpp2::assert_not_null(std::move(lines)), true);

        cpp2::Default.expects(std::ssize(CPP2_UFCS_0(get_map, (*cpp2::assert_not_null(tokens)))) == 1, "");

        //  Now parse this single declaration from
        //  the lexed tokens
        return CPP2_UFCS(parse_one_declaration, parser, 
            (*cpp2::assert_not_null(CPP2_UFCS_0(begin, CPP2_UFCS_0(get_map, *cpp2::assert_not_null(std::move(tokens)))))).second, 
            *cpp2::assert_not_null(generated_tokens)
        ); 
    }

#line 136 "reflect.h2"
    [[nodiscard]] auto compiler_services::position() const -> source_position

    {
        return {  }; 
    }

#line 145 "reflect.h2"
    auto compiler_services::require(

        cpp2::impl::in<bool> b, 
        cpp2::impl::in<std::string_view> msg
    ) const& -> void
    {
        if (!(b)) {
            error(msg);
        }
    }

#line 156 "reflect.h2"
    auto compiler_services::error(cpp2::impl::in<std::string_view> msg) const& -> void
    {
        auto message {cpp2::as_<std::string>(msg)}; 
        if (!(CPP2_UFCS_0(empty, metafunction_name))) {
            message = "while applying @" + metafunction_name + " - " + message;
        }
        static_cast<void>(CPP2_UFCS(emplace_back, (*cpp2::assert_not_null(errors)), position(), std::move(message)));
    }

#line 168 "reflect.h2"
    auto compiler_services::report_violation(auto const& msg) const& -> void{
        error(msg);
        throw(std::runtime_error(
            "  ==> programming bug found in metafunction @" + cpp2::to_string(metafunction_name) + " "
            "- contract violation - see previous errors"
        ));
    }

#line 176 "reflect.h2"
    [[nodiscard]] auto compiler_services::is_active() const& -> auto { return true;  }

    compiler_services::~compiler_services() noexcept{}
compiler_services::compiler_services(compiler_services const& that)
                                     : errors{ that.errors }
                                     , includes{ that.includes }
                                     , extra_cpp1{ that.extra_cpp1 }
                                     , extra_build{ that.extra_build }
                                     , file_name{ that.file_name }
                                     , errors_original_size{ that.errors_original_size }
                                     , generated_tokens{ that.generated_tokens }
                                     , parser{ that.parser }
                                     , metafunction_name{ that.metafunction_name }
                                     , metafunction_args{ that.metafunction_args }
                                     , metafunctions_used{ that.metafunctions_used }{}
compiler_services::compiler_services(compiler_services&& that) noexcept
                                     : errors{ std::move(that).errors }
                                     , includes{ std::move(that).includes }
                                     , extra_cpp1{ std::move(that).extra_cpp1 }
                                     , extra_build{ std::move(that).extra_build }
                                     , file_name{ std::move(that).file_name }
                                     , errors_original_size{ std::move(that).errors_original_size }
                                     , generated_tokens{ std::move(that).generated_tokens }
                                     , parser{ std::move(that).parser }
                                     , metafunction_name{ std::move(that).metafunction_name }
                                     , metafunction_args{ std::move(that).metafunction_args }
                                     , metafunctions_used{ std::move(that).metafunctions_used }{}

#line 232 "reflect.h2"
    declaration_base::declaration_base(

#line 218 "reflect.h2"
    template <typename T> reflection_base<T>::reflection_base(

        cpp2::impl::in<T*> n_, 
        cpp2::impl::in<compiler_services> s
    )
        : compiler_services{ s }
        , n{ n_ }
#line 237 "reflect.h2"
    {

#line 240 "reflect.h2"
        if (cpp2::cpp2_default.is_active() && !(n) ) { cpp2::cpp2_default.report_violation(CPP2_CONTRACT_MSG("a meta::declaration must point to a valid declaration_node, not null")); }
    }

    [[nodiscard]] auto declaration_base::position() const -> source_position { return CPP2_UFCS_0(position, (*cpp2::assert_not_null(n)));  }

    [[nodiscard]] auto declaration_base::print() const& -> std::string { return CPP2_UFCS(pretty_print_visualize, (*cpp2::assert_not_null(n)), 0);  }

    template <typename T> reflection_base<T>::~reflection_base() noexcept{}
template <typename T> reflection_base<T>::reflection_base(reflection_base const& that)
                                     : compiler_services{ static_cast<compiler_services const&>(that) }
                                     , n{ that.n }{}
template <typename T> reflection_base<T>::reflection_base(reflection_base&& that) noexcept
                                     : compiler_services{ static_cast<compiler_services&&>(that) }
                                     , n{ std::move(that).n }{}

#line 256 "reflect.h2"
    declaration::declaration(

        cpp2::impl::in<declaration_node*> n_, 
        cpp2::impl::in<compiler_services> s
    )
        : declaration_base{ n_, s }
#line 261 "reflect.h2"
    {

    }

    [[nodiscard]] auto declaration::is_public() const& -> bool { return CPP2_UFCS_0(is_public, (*cpp2::assert_not_null(n))); }
    [[nodiscard]] auto declaration::is_protected() const& -> bool { return CPP2_UFCS_0(is_protected, (*cpp2::assert_not_null(n))); }
    [[nodiscard]] auto declaration::is_private() const& -> bool { return CPP2_UFCS_0(is_private, (*cpp2::assert_not_null(n))); }
    [[nodiscard]] auto declaration::is_default_access() const& -> bool { return CPP2_UFCS_0(is_default_access, (*cpp2::assert_not_null(n)));  }

    auto declaration::default_to_public() & -> void { static_cast<void>(CPP2_UFCS_0(make_public, (*cpp2::assert_not_null(n)))); }
    auto declaration::default_to_protected() & -> void { static_cast<void>(CPP2_UFCS_0(make_protected, (*cpp2::assert_not_null(n))));  }
    auto declaration::default_to_private() & -> void { static_cast<void>(CPP2_UFCS_0(make_private, (*cpp2::assert_not_null(n)))); }

    [[nodiscard]] auto declaration::make_public() & -> bool { return CPP2_UFCS_0(make_public, (*cpp2::assert_not_null(n))); }
    [[nodiscard]] auto declaration::make_protected() & -> bool { return CPP2_UFCS_0(make_protected, (*cpp2::assert_not_null(n))); }
    [[nodiscard]] auto declaration::make_private() & -> bool { return CPP2_UFCS_0(make_private, (*cpp2::assert_not_null(n))); }

    [[nodiscard]] auto declaration::has_name() const& -> bool { return CPP2_UFCS_0(has_name, (*cpp2::assert_not_null(n))); }
    [[nodiscard]] auto declaration::has_name(cpp2::in<std::string_view> s) const& -> bool { return CPP2_UFCS(has_name, (*cpp2::assert_not_null(n)), s); }

#line 281 "reflect.h2"
    [[nodiscard]] auto declaration::name() const& -> std::string_view{
        if (has_name()) {return CPP2_UFCS_0(as_string_view, (*cpp2::assert_not_null(CPP2_UFCS_0(name, *cpp2::assert_not_null(n))))); }
        else          { return ""; }
    }

    [[nodiscard]] auto declaration::has_initializer() const& -> bool { return CPP2_UFCS_0(has_initializer, (*cpp2::assert_not_null(n)));  }

    [[nodiscard]] auto declaration::is_global() const& -> bool { return CPP2_UFCS_0(is_global, (*cpp2::assert_not_null(n))); }
    [[nodiscard]] auto declaration::is_function() const& -> bool { return CPP2_UFCS_0(is_function, (*cpp2::assert_not_null(n))); }
    [[nodiscard]] auto declaration::is_object() const& -> bool { return CPP2_UFCS_0(is_object, (*cpp2::assert_not_null(n))); }
    [[nodiscard]] auto declaration::is_base_object() const& -> bool { return CPP2_UFCS_0(is_base_object, (*cpp2::assert_not_null(n))); }
    [[nodiscard]] auto declaration::is_member_object() const& -> bool { return CPP2_UFCS_0(is_member_object, (*cpp2::assert_not_null(n)));  }
    [[nodiscard]] auto declaration::is_type() const& -> bool { return CPP2_UFCS_0(is_type, (*cpp2::assert_not_null(n))); }
    [[nodiscard]] auto declaration::is_namespace() const& -> bool { return CPP2_UFCS_0(is_namespace, (*cpp2::assert_not_null(n))); }
    [[nodiscard]] auto declaration::is_alias() const& -> bool { return CPP2_UFCS_0(is_alias, (*cpp2::assert_not_null(n))); }

    [[nodiscard]] auto declaration::is_type_alias() const& -> bool { return CPP2_UFCS_0(is_type_alias, (*cpp2::assert_not_null(n))); }
    [[nodiscard]] auto declaration::is_namespace_alias() const& -> bool { return CPP2_UFCS_0(is_namespace_alias, (*cpp2::assert_not_null(n)));  }
    [[nodiscard]] auto declaration::is_object_alias() const& -> bool { return CPP2_UFCS_0(is_object_alias, (*cpp2::assert_not_null(n))); }

    [[nodiscard]] auto declaration::is_function_expression() const& -> bool { return CPP2_UFCS_0(is_function_expression, (*cpp2::assert_not_null(n)));  }

#line 303 "reflect.h2"
    [[nodiscard]] auto declaration::as_function() const& -> function_declaration { return function_declaration(n, (*this));  }
#line 304 "reflect.h2"
    [[nodiscard]] auto declaration::as_object() const& -> object_declaration { return object_declaration(n, (*this)); }
#line 305 "reflect.h2"
    [[nodiscard]] auto declaration::as_type() const& -> type_declaration { return type_declaration(n, (*this)); }
#line 306 "reflect.h2"
    [[nodiscard]] auto declaration::as_alias() const& -> alias_declaration { return alias_declaration(n, (*this)); }

#line 308 "reflect.h2"
    [[nodiscard]] auto declaration::get_parent() const& -> declaration { return declaration((*cpp2::impl::assert_not_null(n)).parent_declaration, (*this)); }

    [[nodiscard]] auto declaration::parent_is_function() const& -> bool { return CPP2_UFCS_0(parent_is_function, (*cpp2::assert_not_null(n))); }
    [[nodiscard]] auto declaration::parent_is_object() const& -> bool { return CPP2_UFCS_0(parent_is_object, (*cpp2::assert_not_null(n))); }
    [[nodiscard]] auto declaration::parent_is_type() const& -> bool { return CPP2_UFCS_0(parent_is_type, (*cpp2::assert_not_null(n))); }
    [[nodiscard]] auto declaration::parent_is_namespace() const& -> bool { return CPP2_UFCS_0(parent_is_namespace, (*cpp2::assert_not_null(n))); }
    [[nodiscard]] auto declaration::parent_is_alias() const& -> bool { return CPP2_UFCS_0(parent_is_alias, (*cpp2::assert_not_null(n))); }

    [[nodiscard]] auto declaration::parent_is_type_alias() const& -> bool { return CPP2_UFCS_0(parent_is_type_alias, (*cpp2::assert_not_null(n))); }
    [[nodiscard]] auto declaration::parent_is_namespace_alias() const& -> bool { return CPP2_UFCS_0(parent_is_namespace_alias, (*cpp2::assert_not_null(n)));  }
    [[nodiscard]] auto declaration::parent_is_object_alias() const& -> bool { return CPP2_UFCS_0(parent_is_object_alias, (*cpp2::assert_not_null(n))); }

    [[nodiscard]] auto declaration::parent_is_polymorphic() const& -> bool { return CPP2_UFCS_0(parent_is_polymorphic, (*cpp2::assert_not_null(n)));  }

#line 322 "reflect.h2"
    auto declaration::mark_for_removal_from_enclosing_type() & -> void
                                                    // this precondition should be sufficient ...
    {
        cpp2::Type.expects(parent_is_type(), "");
#line 292 "reflect.h2"
        auto test {CPP2_UFCS_0(type_member_mark_for_removal, (*cpp2::assert_not_null(n)))}; 
        cpp2::Default.expects(std::move(test), ""); // ... to ensure this assert is true
    }

    declaration::~declaration() noexcept{}
declaration::declaration(declaration const& that)
                                     : reflection_base<declaration_node>{ static_cast<reflection_base<declaration_node> const&>(that) }{}
declaration::declaration(declaration&& that) noexcept
                                     : reflection_base<declaration_node>{ static_cast<reflection_base<declaration_node>&&>(that) }{}

#line 338 "reflect.h2"
    function_declaration::function_declaration(

        cpp2::impl::in<declaration_node*> n_, 
        cpp2::impl::in<compiler_services> s
    )
        : declaration{ n_, s }
#line 343 "reflect.h2"
    {

        cpp2::Default.expects(CPP2_UFCS_0(is_function, (*cpp2::assert_not_null(n))), "");
    }

    [[nodiscard]] auto function_declaration::index_of_parameter_named(cpp2::in<std::string_view> s) const& -> int { return CPP2_UFCS(index_of_parameter_named, (*cpp2::assert_not_null(n)), s); }
    [[nodiscard]] auto function_declaration::has_parameter_named(cpp2::in<std::string_view> s) const& -> bool { return CPP2_UFCS(has_parameter_named, (*cpp2::assert_not_null(n)), s); }
    [[nodiscard]] auto function_declaration::has_in_parameter_named(cpp2::in<std::string_view> s) const& -> bool { return CPP2_UFCS(has_in_parameter_named, (*cpp2::assert_not_null(n)), s); }
    [[nodiscard]] auto function_declaration::has_out_parameter_named(cpp2::in<std::string_view> s) const& -> bool { return CPP2_UFCS(has_out_parameter_named, (*cpp2::assert_not_null(n)), s); }
    [[nodiscard]] auto function_declaration::has_move_parameter_named(cpp2::in<std::string_view> s) const& -> bool { return CPP2_UFCS(has_move_parameter_named, (*cpp2::assert_not_null(n)), s); }

    [[nodiscard]] auto function_declaration::has_parameter_with_name_and_pass(cpp2::in<std::string_view> s, cpp2::in<passing_style> pass) const& -> bool { 
                                                  return CPP2_UFCS(has_parameter_with_name_and_pass, (*cpp2::assert_not_null(n)), s, pass);  }
    [[nodiscard]] auto function_declaration::is_function_with_this() const& -> bool { return CPP2_UFCS_0(is_function_with_this, (*cpp2::assert_not_null(n))); }
    [[nodiscard]] auto function_declaration::is_virtual() const& -> bool { return CPP2_UFCS_0(is_virtual_function, (*cpp2::assert_not_null(n))); }
    [[nodiscard]] auto function_declaration::is_defaultable() const& -> bool { return CPP2_UFCS_0(is_defaultable_function, (*cpp2::assert_not_null(n))); }
    [[nodiscard]] auto function_declaration::is_constructor() const& -> bool { return CPP2_UFCS_0(is_constructor, (*cpp2::assert_not_null(n))); }
    [[nodiscard]] auto function_declaration::is_default_constructor() const& -> bool { return CPP2_UFCS_0(is_default_constructor, (*cpp2::assert_not_null(n))); }
    [[nodiscard]] auto function_declaration::is_move() const& -> bool { return CPP2_UFCS_0(is_move, (*cpp2::assert_not_null(n))); }
    [[nodiscard]] auto function_declaration::is_swap() const& -> bool { return CPP2_UFCS_0(is_swap, (*cpp2::assert_not_null(n))); }
    [[nodiscard]] auto function_declaration::is_constructor_with_that() const& -> bool { return CPP2_UFCS_0(is_constructor_with_that, (*cpp2::assert_not_null(n))); }
    [[nodiscard]] auto function_declaration::is_constructor_with_in_that() const& -> bool { return CPP2_UFCS_0(is_constructor_with_in_that, (*cpp2::assert_not_null(n))); }
    [[nodiscard]] auto function_declaration::is_constructor_with_move_that() const& -> bool { return CPP2_UFCS_0(is_constructor_with_move_that, (*cpp2::assert_not_null(n)));  }
    [[nodiscard]] auto function_declaration::is_assignment() const& -> bool { return CPP2_UFCS_0(is_assignment, (*cpp2::assert_not_null(n))); }
    [[nodiscard]] auto function_declaration::is_assignment_with_that() const& -> bool { return CPP2_UFCS_0(is_assignment_with_that, (*cpp2::assert_not_null(n))); }
    [[nodiscard]] auto function_declaration::is_assignment_with_in_that() const& -> bool { return CPP2_UFCS_0(is_assignment_with_in_that, (*cpp2::assert_not_null(n))); }
    [[nodiscard]] auto function_declaration::is_assignment_with_move_that() const& -> bool { return CPP2_UFCS_0(is_assignment_with_move_that, (*cpp2::assert_not_null(n)));  }
    [[nodiscard]] auto function_declaration::is_destructor() const& -> bool { return CPP2_UFCS_0(is_destructor, (*cpp2::assert_not_null(n))); }

#line 376 "reflect.h2"
    [[nodiscard]] auto function_declaration::is_copy_or_move() const& -> bool { return is_constructor_with_that() || is_assignment_with_that(); }

    [[nodiscard]] auto function_declaration::has_declared_return_type() const& -> bool { return CPP2_UFCS_0(has_declared_return_type, (*cpp2::assert_not_null(n))); }
    [[nodiscard]] auto function_declaration::has_bool_return_type() const& -> bool { return CPP2_UFCS_0(has_bool_return_type, (*cpp2::assert_not_null(n))); }
    [[nodiscard]] auto function_declaration::has_non_void_return_type() const& -> bool { return CPP2_UFCS_0(has_non_void_return_type, (*cpp2::assert_not_null(n))); }

    [[nodiscard]] auto function_declaration::unnamed_return_type() const& -> std::string { return CPP2_UFCS_0(unnamed_return_type_to_string, (*cpp2::assert_not_null(n))); }

    [[nodiscard]] auto function_declaration::is_binary_comparison_function() const& -> bool { return CPP2_UFCS_0(is_binary_comparison_function, (*cpp2::assert_not_null(n)));  }

    auto function_declaration::default_to_virtual() & -> void { static_cast<void>(CPP2_UFCS_0(make_function_virtual, (*cpp2::assert_not_null(n)))); }

    [[nodiscard]] auto function_declaration::make_virtual() & -> bool { return CPP2_UFCS_0(make_function_virtual, (*cpp2::assert_not_null(n))); }

    function_declaration::function_declaration(function_declaration const& that)
                                : declaration{ static_cast<declaration const&>(that) }{}

#line 362 "reflect.h2"
    object_declaration::object_declaration(

        declaration_node* n_, 
        cpp2::in<compiler_services> s
    )
        : declaration{ n_, s }
#line 367 "reflect.h2"
    {

        cpp2::Default.expects(CPP2_UFCS_0(is_object, (*cpp2::assert_not_null(n))), "");
    }

    [[nodiscard]] auto object_declaration::is_const() const& -> bool { return CPP2_UFCS_0(is_const, (*cpp2::assert_not_null(n))); }
    [[nodiscard]] auto object_declaration::has_wildcard_type() const& -> bool { return CPP2_UFCS_0(has_wildcard_type, (*cpp2::assert_not_null(n)));  }

#line 397 "reflect.h2"
    auto function_declaration::default_to_virtual() & -> void { static_cast<void>(CPP2_UFCS(make_function_virtual)((*cpp2::impl::assert_not_null(n)))); }

#line 399 "reflect.h2"
    [[nodiscard]] auto function_declaration::make_virtual() & -> bool { return CPP2_UFCS(make_function_virtual)((*cpp2::impl::assert_not_null(n))); }

#line 401 "reflect.h2"
    auto function_declaration::add_initializer(cpp2::impl::in<std::string_view> source) & -> void

#line 404 "reflect.h2"
    {
        if ((*this).is_active() && !(!(has_initializer())) ) { (*this).report_violation(CPP2_CONTRACT_MSG("cannot add an initializer to a function that already has one")); }
        if ((*this).is_active() && !(parent_is_type()) ) { (*this).report_violation(CPP2_CONTRACT_MSG("cannot add an initializer to a function that isn't in a type scope")); }
        //require( !has_initializer(),
        //         "cannot add an initializer to a function that already has one");
        //require( parent_is_type(),
        //         "cannot add an initializer to a function that isn't in a type scope");

#line 410 "reflect.h2"
        auto stmt {parse_statement(source)}; 
        if (!((cpp2::impl::as_<bool>(stmt)))) {
            error("cannot add an initializer that is not a valid statement");
            return ; 
        }
        require(CPP2_UFCS(add_function_initializer)((*cpp2::impl::assert_not_null(n)), std::move(cpp2::move(stmt))), 
                 std::string("unexpected error while attempting to add initializer"));
    }

    function_declaration::function_declaration(function_declaration const& that)
                                     : declaration{ static_cast<declaration const&>(that) }{}
function_declaration::function_declaration(function_declaration&& that) noexcept
                                     : declaration{ static_cast<declaration&&>(that) }{}

#line 428 "reflect.h2"
    object_declaration::object_declaration(

        cpp2::impl::in<declaration_node*> n_, 
        cpp2::impl::in<compiler_services> s
    )
        : declaration{ n_, s }
#line 433 "reflect.h2"
    {

        if (cpp2::cpp2_default.is_active() && !(CPP2_UFCS(is_object)((*cpp2::impl::assert_not_null(n)))) ) { cpp2::cpp2_default.report_violation(""); }
    }

#line 438 "reflect.h2"
    [[nodiscard]] auto object_declaration::is_const() const& -> bool { return CPP2_UFCS(is_const)((*cpp2::impl::assert_not_null(n))); }
#line 439 "reflect.h2"
    [[nodiscard]] auto object_declaration::has_wildcard_type() const& -> bool { return CPP2_UFCS(has_wildcard_type)((*cpp2::impl::assert_not_null(n)));  }

#line 441 "reflect.h2"
    [[nodiscard]] auto object_declaration::type() const& -> std::string{
        auto ret {CPP2_UFCS_0(object_type, (*cpp2::assert_not_null(n)))}; 
        require(!(contains(ret, "(*ERROR*)")), 
                 "cannot to_string this type: " + ret);
        return ret; 
    }

#line 448 "reflect.h2"
    [[nodiscard]] auto object_declaration::initializer() const& -> std::string{
        auto ret {CPP2_UFCS_0(object_initializer, (*cpp2::assert_not_null(n)))}; 
        require(!(contains(ret, "(*ERROR*)")), 
                 "cannot to_string this initializer: " + ret);
        return ret; 
    }

    object_declaration::object_declaration(object_declaration const& that)
                                     : declaration{ static_cast<declaration const&>(that) }{}
object_declaration::object_declaration(object_declaration&& that) noexcept
                                     : declaration{ static_cast<declaration&&>(that) }{}

#line 464 "reflect.h2"
    type_declaration::type_declaration(

#line 475 "reflect.h2"
    type_or_namespace_declaration::type_or_namespace_declaration(

        cpp2::impl::in<declaration_node*> n_, 
        cpp2::impl::in<compiler_services> s
    )
        : declaration{ n_, s }
#line 469 "reflect.h2"
    {

        cpp2::Default.expects(CPP2_UFCS_0(is_type, (*cpp2::assert_not_null(n))), "");
    }

#line 474 "reflect.h2"
    auto type_declaration::reserve_names(cpp2::impl::in<std::string_view> name, auto&& ...etc) const& -> void
    {                           // etc is not declared ':string_view' for compatibility with GCC 10.x
        for ( 
             auto const& m : get_members() ) {
            CPP2_UFCS(require, m, !(CPP2_UFCS(has_name, m, name)), 
                       "in a '" + cpp2::to_string(get_metafunction_name()) + "' type, the name '" + cpp2::to_string(name) + "' is reserved for use by the '" + cpp2::to_string(get_metafunction_name()) + "' implementation");
        }
        if constexpr (!(CPP2_PACK_EMPTY(etc))) {
            reserve_names(CPP2_FORWARD(etc)...);
        }
    }

    [[nodiscard]] auto type_declaration::is_polymorphic() const& -> bool { return CPP2_UFCS_0(is_polymorphic, (*cpp2::assert_not_null(n))); }
    [[nodiscard]] auto type_declaration::is_final() const& -> bool { return CPP2_UFCS_0(is_type_final, (*cpp2::assert_not_null(n))); }
    [[nodiscard]] auto type_declaration::make_final() & -> bool { return CPP2_UFCS_0(make_type_final, (*cpp2::assert_not_null(n))); }

#line 492 "reflect.h2"
    [[nodiscard]] auto type_declaration::get_member_functions() const& -> std::vector<function_declaration>

    {
        std::vector<function_declaration> ret {}; 
        for ( auto const& d : CPP2_UFCS(get_type_scope_declarations, (*cpp2::assert_not_null(n)), declaration_node::functions) ) {
            static_cast<void>(CPP2_UFCS(emplace_back, ret, d, (*this)));
        }
        return ret; 
    }

#line 503 "reflect.h2"
    [[nodiscard]] auto type_declaration::get_member_functions_needing_initializer() const& -> std::vector<function_declaration>

    {
        std::vector<function_declaration> ret {}; 
        for ( 
             auto const& d : CPP2_UFCS(get_nested_declarations)((*cpp2::impl::assert_not_null(n)), declaration_node::functions) ) 
        if ( !(CPP2_UFCS(has_initializer)((*cpp2::impl::assert_not_null(d)))) 
            && !(CPP2_UFCS(is_virtual_function)((*cpp2::impl::assert_not_null(d)))) 
            && !(CPP2_UFCS(is_defaultable_function)((*cpp2::impl::assert_not_null(d))))) 
        {
            static_cast<void>(CPP2_UFCS(emplace_back)(ret, d, (*this)));
        }
        return ret; 
    }

#line 518 "reflect.h2"
    [[nodiscard]] auto type_declaration::get_member_objects() const& -> std::vector<object_declaration>

    {
        std::vector<object_declaration> ret {}; 
        for ( auto const& d : CPP2_UFCS(get_type_scope_declarations, (*cpp2::assert_not_null(n)), declaration_node::objects) ) {
            static_cast<void>(CPP2_UFCS(emplace_back, ret, d, (*this)));
        }
        return ret; 
    }

#line 528 "reflect.h2"
    [[nodiscard]] auto type_declaration::get_member_types() const& -> std::vector<type_declaration>

    {
        std::vector<type_declaration> ret {}; 
        for ( auto const& d : CPP2_UFCS(get_type_scope_declarations, (*cpp2::assert_not_null(n)), declaration_node::types) ) {
            static_cast<void>(CPP2_UFCS(emplace_back, ret, d, (*this)));
        }
        return ret; 
    }

#line 538 "reflect.h2"
    [[nodiscard]] auto type_declaration::get_member_aliases() const& -> std::vector<alias_declaration>

    {
        std::vector<alias_declaration> ret {}; 
        for ( auto const& d : CPP2_UFCS(get_type_scope_declarations, (*cpp2::assert_not_null(n)), declaration_node::aliases) ) {
            static_cast<void>(CPP2_UFCS(emplace_back, ret, d, (*this)));
        }
        return ret; 
    }

#line 548 "reflect.h2"
    [[nodiscard]] auto type_declaration::get_members() const& -> std::vector<declaration>

    {
        std::vector<declaration> ret {}; 
        for ( auto const& d : CPP2_UFCS(get_type_scope_declarations, (*cpp2::assert_not_null(n)), declaration_node::all) ) {
            static_cast<void>(CPP2_UFCS(emplace_back, ret, d, (*this)));
        }
        return ret; 
    }

#line 558 "reflect.h2"
    [[nodiscard]] auto type_declaration::query_declared_value_set_functions() const& -> query_declared_value_set_functions_ret

#line 565 "reflect.h2"
    {
            cpp2::deferred_init<bool> out_this_in_that;
            cpp2::deferred_init<bool> out_this_move_that;
            cpp2::deferred_init<bool> inout_this_in_that;
            cpp2::deferred_init<bool> inout_this_move_that;
#line 482 "reflect.h2"
        auto declared {CPP2_UFCS_0(find_declared_value_set_functions, (*cpp2::assert_not_null(n)))}; 
        out_this_in_that.construct(declared.out_this_in_that != nullptr);
        out_this_move_that.construct(declared.out_this_move_that != nullptr);
        inout_this_in_that.construct(declared.inout_this_in_that != nullptr);
        inout_this_move_that.construct(cpp2::move(declared).inout_this_move_that != nullptr);
    return  { std::move(out_this_in_that.value()), std::move(out_this_move_that.value()), std::move(inout_this_in_that.value()), std::move(inout_this_move_that.value()) }; }

#line 573 "reflect.h2"
    auto type_declaration::add_member(cpp2::impl::in<std::string_view> source) & -> void
    {
        auto decl {parse_statement(source)}; 
        if (!(decl) || !(CPP2_UFCS(add_type_member, (*cpp2::assert_not_null(n)), std::move(decl)))) {
            error(std::string("error attempting to add member:\n") + source);
        }
        if (!(CPP2_UFCS(is_declaration)((*cpp2::impl::assert_not_null(decl))))) {
            error("cannot add a member that is not a declaration");
        }
        require(CPP2_UFCS(add_type_or_namespace_member)((*cpp2::impl::assert_not_null(n)), std::move(cpp2::move(decl))), 
                 std::string("unexpected error while attempting to add member:\n") + source);
    }

    auto type_declaration::remove_marked_members() & -> void { CPP2_UFCS_0(type_remove_marked_members, (*cpp2::assert_not_null(n)));  }
    auto type_declaration::remove_all_members() & -> void { CPP2_UFCS_0(type_remove_all_members, (*cpp2::assert_not_null(n))); }

    auto type_declaration::disable_member_function_generation() & -> void { CPP2_UFCS_0(type_disable_member_function_generation, (*cpp2::assert_not_null(n)));  }

    type_declaration::type_declaration(type_declaration const& that)
                                     : type_or_namespace_declaration{ static_cast<type_or_namespace_declaration const&>(that) }{}
type_declaration::type_declaration(type_declaration&& that) noexcept
                                     : type_or_namespace_declaration{ static_cast<type_or_namespace_declaration&&>(that) }{}

#line 601 "reflect.h2"
    alias_declaration::alias_declaration(

        cpp2::impl::in<declaration_node*> n_, 
        cpp2::impl::in<compiler_services> s
    )
        : declaration{ n_, s }
#line 606 "reflect.h2"
    {

        cpp2::Default.expects(CPP2_UFCS_0(is_alias, (*cpp2::assert_not_null(n))), "");
    }

    alias_declaration::alias_declaration(alias_declaration const& that)
                                     : declaration{ static_cast<declaration const&>(that) }{}
alias_declaration::alias_declaration(alias_declaration&& that) noexcept
                                     : declaration{ static_cast<declaration&&>(that) }{}

#line 625 "reflect.h2"
auto add_virtual_destructor(meta::type_declaration& t) -> void
{
    CPP2_UFCS(add_member, t, "operator=: (virtual move this) = { }");
}

#line 643 "reflect.h2"
auto interface(meta::type_declaration& t) -> void
{
    auto has_dtor {false}; 

    for ( auto& m : CPP2_UFCS_0(get_members, t) ) 
    {
        CPP2_UFCS(require, m, !(CPP2_UFCS_0(is_object, m)), 
                   "interfaces may not contain data objects");
        if (CPP2_UFCS_0(is_function, m)) {
            auto mf {CPP2_UFCS_0(as_function, m)}; 
            CPP2_UFCS(require, mf, !(CPP2_UFCS_0(is_copy_or_move, mf)), 
                        "interfaces may not copy or move; consider a virtual clone() instead");
            CPP2_UFCS(require, mf, !(CPP2_UFCS_0(has_initializer, mf)), 
                        "interface functions must not have a function body; remove the '=' initializer");
            CPP2_UFCS(require, mf, CPP2_UFCS_0(make_public, mf), 
                        "interface functions must be public");
            CPP2_UFCS_0(default_to_virtual, mf);
            has_dtor |= CPP2_UFCS_0(is_destructor, mf);
        }
    }

    if (!(std::move(has_dtor))) {
        CPP2_UFCS_0(add_virtual_destructor, t);
    }
}

#line 689 "reflect.h2"
auto polymorphic_base(meta::type_declaration& t) -> void
{
    auto has_dtor {false}; 

    for ( auto& mf : CPP2_UFCS_0(get_member_functions, t) ) 
    {
        if (CPP2_UFCS_0(is_default_access, mf)) {
            CPP2_UFCS_0(default_to_public, mf);
        }
        CPP2_UFCS(require, mf, !(CPP2_UFCS_0(is_copy_or_move, mf)), 
                    "polymorphic base types may not copy or move; consider a virtual clone() instead");
        if (CPP2_UFCS_0(is_destructor, mf)) {
            has_dtor = true;
            CPP2_UFCS(require, mf, ((CPP2_UFCS_0(is_public, mf) || CPP2_UFCS_0(is_default_access, mf)) && CPP2_UFCS_0(is_virtual, mf)) 
                        || (CPP2_UFCS_0(is_protected, mf) && !(CPP2_UFCS_0(is_virtual, mf))), 
                        "a polymorphic base type destructor must be public and virtual, or protected and nonvirtual");
        }
    }

    if (!(std::move(has_dtor))) {
        CPP2_UFCS_0(add_virtual_destructor, t);
    }
}

#line 734 "reflect.h2"
auto ordered_impl(
    meta::type_declaration& t, 
    cpp2::impl::in<std::string_view> ordering// must be "strong_ordering" etc.
) -> void
{
    auto has_spaceship {false}; 

    for ( auto& mf : CPP2_UFCS_0(get_member_functions, t) ) 
    {
        if (CPP2_UFCS(has_name, mf, "operator<=>")) {
            has_spaceship = true;
            auto return_name {CPP2_UFCS_0(unnamed_return_type, mf)}; 
            if (CPP2_UFCS(find, return_name, ordering) == return_name.npos) 
            {
                CPP2_UFCS(error, mf, "operator<=> must return std::" + cpp2::as_<std::string>(ordering));
            }
        }
    }

    if (!(std::move(has_spaceship))) {
        CPP2_UFCS(add_member, t, "operator<=>: (this, that) -> std::" + (cpp2::as_<std::string>(ordering)) + ";");
    }
}

#line 763 "reflect.h2"
auto ordered(meta::type_declaration& t) -> void
{
    ordered_impl(t, "strong_ordering");
}

#line 771 "reflect.h2"
auto weakly_ordered(meta::type_declaration& t) -> void
{
    ordered_impl(t, "weak_ordering");
}

#line 779 "reflect.h2"
auto partially_ordered(meta::type_declaration& t) -> void
{
    ordered_impl(t, "partial_ordering");
}

#line 801 "reflect.h2"
auto copyable(meta::type_declaration& t) -> void
{
    //  If the user explicitly wrote any of the copy/move functions,
    //  they must also have written the most general one - we can't
    //  assume we can safely generate it for them since they've opted
    //  into customized semantics
    auto smfs {CPP2_UFCS_0(query_declared_value_set_functions, t)}; 
    if ( !(smfs.out_this_in_that) 
        && (
            smfs.out_this_move_that 
            || smfs.inout_this_in_that 
            || smfs.inout_this_move_that)) 

    {
        CPP2_UFCS(error, t, "this type is partially copyable/movable - when you provide any of the more-specific operator= signatures, you must also provide the one with the general signature (out this, that); alternatively, consider removing all the operator= functions and let them all be generated for you with default memberwise semantics");
    }
    else {if (!(std::move(smfs).out_this_in_that)) {
        CPP2_UFCS(add_member, t, "operator=: (out this, that) = { }");
    }}
}

#line 835 "reflect.h2"
auto basic_value(meta::type_declaration& t) -> void
{
    CPP2_UFCS_0(copyable, t);

    auto has_default_ctor {false}; 
    for ( auto& mf : CPP2_UFCS_0(get_member_functions, t) ) {
        has_default_ctor |= CPP2_UFCS_0(is_default_constructor, mf);
        CPP2_UFCS(require, mf, !(CPP2_UFCS_0(is_protected, mf)) && !(CPP2_UFCS_0(is_virtual, mf)), 
                    "a value type may not have a protected or virtual function");
        CPP2_UFCS(require, mf, !(CPP2_UFCS_0(is_destructor, mf)) || CPP2_UFCS_0(is_public, mf) || CPP2_UFCS_0(is_default_access, mf), 
                    "a value type may not have a non-public destructor");
    }

    if (!(std::move(has_default_ctor))) {
        CPP2_UFCS(add_member, t, "operator=: (out this) = { }");
    }
}

#line 863 "reflect.h2"
auto value(meta::type_declaration& t) -> void
{
    CPP2_UFCS_0(ordered, t);
    CPP2_UFCS_0(basic_value, t);
}

#line 869 "reflect.h2"
auto weakly_ordered_value(meta::type_declaration& t) -> void
{
    CPP2_UFCS_0(weakly_ordered, t);
    CPP2_UFCS_0(basic_value, t);
}

#line 875 "reflect.h2"
auto partially_ordered_value(meta::type_declaration& t) -> void
{
    CPP2_UFCS_0(partially_ordered, t);
    CPP2_UFCS_0(basic_value, t);
}

#line 904 "reflect.h2"
auto cpp1_rule_of_zero(meta::type_declaration& t) -> void
{
    for ( auto& mf : CPP2_UFCS(get_member_functions)(t) ) 
    {
        CPP2_UFCS(require)(t, !(CPP2_UFCS(is_constructor_with_that)(mf)) 
                   && !(CPP2_UFCS(is_assignment_with_that)(mf)) 
                   && !(CPP2_UFCS(is_destructor)(mf)), 
                   "the rule of zero requires no copy/move/destructor functions");
    }
    CPP2_UFCS(disable_member_function_generation)(t);
}

#line 941 "reflect.h2"
auto cpp2_struct(meta::type_declaration& t) -> void
{
    for ( auto& m : CPP2_UFCS_0(get_members, t) ) 
    {
        CPP2_UFCS(require, m, CPP2_UFCS_0(make_public, m), 
                   "all struct members must be public");
        if (CPP2_UFCS_0(is_function, m)) {
            auto mf {CPP2_UFCS_0(as_function, m)}; 
            CPP2_UFCS(require, t, !(CPP2_UFCS_0(is_virtual, mf)), 
                       "a struct may not have a virtual function");
            CPP2_UFCS(require, t, !(CPP2_UFCS(has_name, mf, "operator=")), 
                       "a struct may not have a user-defined operator=");
        }
        else {if (CPP2_UFCS(is_object)(m)) {
            auto mo {CPP2_UFCS(as_object)(m)}; 
            if (CPP2_UFCS(name)(mo) != "this") {
                if (CPP2_UFCS(get_argument)(t, 0) == "noforward") {
                    ctor_params += "" + cpp2::to_string(CPP2_UFCS(name)(mo)) + "_, ";
                }
                else {
                    ctor_params += "forward " + cpp2::to_string(CPP2_UFCS(name)(mo)) + "_ : " + cpp2::to_string(CPP2_UFCS(type)(mo)) + ", ";
                }
                ctor_inits  += "" + cpp2::to_string(CPP2_UFCS(name)(mo)) + " = " + cpp2::to_string(CPP2_UFCS(name)(mo)) + "_; ";
            }
            else {
                ctor_inits += "" + cpp2::to_string(CPP2_UFCS(type)(mo)) + " = (" + cpp2::to_string(CPP2_UFCS(initializer)(mo)) + "); ";
            }
            found_member_without_initializer |= !(CPP2_UFCS(has_initializer)(cpp2::move(mo)));
        }}
    }
    CPP2_UFCS(cpp1_rule_of_zero)(t);

    //  If we found any data members
    if (!(CPP2_UFCS(empty)(ctor_params))) 
    {
        //  Then to enable construction from corresponding values
        //  requires a constructor... an exception to the rule of zero
        CPP2_UFCS(add_member)(t, "    operator=: (implicit out this, " + cpp2::to_string(cpp2::move(ctor_params)) + ") = { " + cpp2::to_string(cpp2::move(ctor_inits)) + " }");

        //  And if all members had initializers, we need a default constructor
        if (!(cpp2::move(found_member_without_initializer))) {
            CPP2_UFCS(add_member)(t, "    operator=: (implicit out this) = { }");
        }
    }
    CPP2_UFCS_0(disable_member_function_generation, t);
}

value_member_info::value_member_info(auto const& name_, auto const& type_, auto const& value_)
                                                               : name{ name_ }
                                                               , type{ type_ }
                                                               , value{ value_ }{}

#line 1011 "reflect.h2"
auto basic_enum(
    meta::type_declaration& t, 
    auto const& nextval, 
    cpp2::impl::in<bool> bitwise
    ) -> void
{
    std::vector<value_member_info> enumerators {}; 
    cpp2::i64 min_value {}; 
    cpp2::i64 max_value {}; 
    cpp2::impl::deferred_init<std::string> underlying_type; 

    CPP2_UFCS(reserve_names, t, "operator=", "operator<=>");
    if (bitwise) {
        CPP2_UFCS(reserve_names, t, "has", "set", "clear", "to_string", "get_raw_value", "none");
    }

    //  1. Gather: The names of all the user-written members, and find/compute the type

    underlying_type.construct(CPP2_UFCS(get_argument, t, 0));// use the first template argument, if there was one

    auto found_non_numeric {false}; 
{
std::string value{"-1"};

#line 1034 "reflect.h2"
    for ( 
          auto const& m : CPP2_UFCS_0(get_members, t) ) 
    if (  CPP2_UFCS_0(is_member_object, m)) 
    {
        CPP2_UFCS(require, m, CPP2_UFCS_0(is_public, m) || CPP2_UFCS_0(is_default_access, m), 
                    "an enumerator cannot be protected or private");

        auto mo {CPP2_UFCS_0(as_object, m)}; 
        if (!(CPP2_UFCS_0(has_wildcard_type, mo))) {
            CPP2_UFCS(error, mo, "an explicit underlying type should be specified as a template argument to the metafunction - try 'enum<u16>' or 'flag_enum<u64>'");
        }

        auto init {CPP2_UFCS_0(initializer, mo)}; 

        auto is_default_or_numeric {is_empty_or_a_decimal_number(init)}; 
        found_non_numeric |= !(CPP2_UFCS_0(empty, init)) && !(is_default_or_numeric);
        CPP2_UFCS(require, m, !(is_default_or_numeric) || !(found_non_numeric) || CPP2_UFCS(has_name, mo, "none"), 
            cpp2::to_string(CPP2_UFCS_0(name, mo)) + ": enumerators with non-numeric values must come after all default and numeric values");

        nextval(value, cpp2::move(init));

        auto v {std::strtoll(&CPP2_ASSERT_IN_BOUNDS_LITERAL(value, 0), nullptr, 10)}; // for non-numeric values we'll just get 0 which is okay for now
        if (cpp2::impl::cmp_less(v,min_value)) {
            min_value = v;
        }
        if (cpp2::impl::cmp_greater(v,max_value)) {
            max_value = cpp2::move(v);
        }

        //  Adding local variable 'e' to work around a Clang warning
        value_member_info e {cpp2::as_<std::string>(CPP2_UFCS_0(name, mo)), "", value}; 
        CPP2_UFCS(push_back, enumerators, e);

        CPP2_UFCS_0(mark_for_removal_from_enclosing_type, mo);
    }
}

#line 1074 "reflect.h2"
    if ((CPP2_UFCS(empty)(enumerators))) {
        CPP2_UFCS(error)(t, "an enumeration must contain at least one enumerator value");
        return ; 
    }

    //  Compute the default underlying type, if it wasn't explicitly specified
    if (underlying_type.value() == "") 
    {
        CPP2_UFCS(require, t, !(std::move(found_non_numeric)), 
            "if you write an enumerator with a non-numeric-literal value, you must specify the enumeration's underlying type");

        if (!(bitwise)) {
            if (cpp2::impl::cmp_greater_eq(min_value,std::numeric_limits<cpp2::i8>::min()) && cpp2::impl::cmp_less_eq(max_value,std::numeric_limits<cpp2::i8>::max())) {
                underlying_type.value() = "i8";
            }
            else {if (cpp2::impl::cmp_greater_eq(min_value,std::numeric_limits<cpp2::i16>::min()) && cpp2::impl::cmp_less_eq(max_value,std::numeric_limits<cpp2::i16>::max())) {
                underlying_type.value() = "i16";
            }
            else {if (cpp2::impl::cmp_greater_eq(min_value,std::numeric_limits<cpp2::i32>::min()) && cpp2::impl::cmp_less_eq(max_value,std::numeric_limits<cpp2::i32>::max())) {
                underlying_type.value() = "i32";
            }
            else {if (cpp2::impl::cmp_greater_eq(cpp2::move(min_value),std::numeric_limits<cpp2::i64>::min()) && cpp2::impl::cmp_less_eq(cpp2::move(max_value),std::numeric_limits<cpp2::i64>::max())) {
                underlying_type.value() = "i64";
            }
            else {
                CPP2_UFCS(error, t, "values are outside the range representable by the largest supported underlying signed type (i64)");
            }}}}
        }
        else {
            auto umax {cpp2::move(max_value) * cpp2::impl::as_<cpp2::u64, 2>()}; 
            if (cpp2::impl::cmp_less_eq(umax,std::numeric_limits<cpp2::u8>::max())) {
                underlying_type.value() = "u8";
            }
            else {if (cpp2::impl::cmp_less_eq(umax,std::numeric_limits<cpp2::u16>::max())) {
                underlying_type.value() = "u16";
            }
            else {if (cpp2::impl::cmp_less_eq(cpp2::move(umax),std::numeric_limits<cpp2::u32>::max())) {
                underlying_type.value() = "u32";
            }
            else {
                underlying_type.value() = "u64";
            }}}
        }
    }

#line 1125 "reflect.h2"
    //  2. Replace: Erase the contents and replace with modified contents
    //
    //  Note that most values and functions are declared as '==' compile-time values, i.e. Cpp1 'constexpr'

    CPP2_UFCS_0(remove_marked_members, t);

    //  Generate all the common material: value and common functions
    CPP2_UFCS(add_member, t, "    _value            : " + cpp2::to_string(underlying_type.value()) + ";");
    CPP2_UFCS(add_member, t, "    private operator= : (implicit out this, _val: i64) == _value = cpp2::unsafe_narrow<" + cpp2::to_string(underlying_type.value()) + ">(_val);");
    CPP2_UFCS(add_member, t, "    get_raw_value     : (this) -> " + cpp2::to_string(std::move(underlying_type.value())) + " == _value;");
    CPP2_UFCS(add_member, t, "    operator=         : (out this, that) == { }");
    CPP2_UFCS(add_member, t, "    operator<=>       : (this, that) -> std::strong_ordering;");

    //  Generate the bitwise operations and 'none' value, if appropriate
    if (bitwise) {
        default_value = "none";
        value_member_info e {"none", "", "0"}; 
        CPP2_UFCS(push_back, enumerators, std::move(e));

        CPP2_UFCS(add_member, t, "    operator|=: ( inout this, that )                 == _value |= that._value;");
        CPP2_UFCS(add_member, t, "    operator&=: ( inout this, that )                 == _value &= that._value;");
        CPP2_UFCS(add_member, t, "    operator^=: ( inout this, that )                 == _value ^= that._value;");
        CPP2_UFCS(add_member, t, "    operator| : (       this, that ) -> " + cpp2::to_string(CPP2_UFCS_0(name, t)) + "  == _value |  that._value;");
        CPP2_UFCS(add_member, t, "    operator& : (       this, that ) -> " + cpp2::to_string(CPP2_UFCS_0(name, t)) + "  == _value &  that._value;");
        CPP2_UFCS(add_member, t, "    operator^ : (       this, that ) -> " + cpp2::to_string(CPP2_UFCS_0(name, t)) + "  == _value ^  that._value;");
        CPP2_UFCS(add_member, t, "    has       : ( inout this, that ) -> bool         == _value &  that._value;");
        CPP2_UFCS(add_member, t, "    set       : ( inout this, that )                 == _value |= that._value;");
        CPP2_UFCS(add_member, t, "    clear     : ( inout this, that )                 == _value &= that._value~;");
    }

    //  Add the enumerators
    for ( auto const& e : enumerators ) {
        CPP2_UFCS(add_member, t, "    " + cpp2::to_string(e.name) + " : " + cpp2::to_string(CPP2_UFCS_0(name, t)) + " == " + cpp2::to_string(e.value) + ";");
    }

    //  Generate the common functions
    CPP2_UFCS(add_member)(t, "    get_raw_value     : (this) -> " + cpp2::to_string(cpp2::move(underlying_type.value())) + " == _value;");
    CPP2_UFCS(add_member)(t, "    operator=         : (out this) == { _value = " + cpp2::to_string(default_value) + "._value; }");
    CPP2_UFCS(add_member)(t, "    operator=         : (out this, that) == { }");
    CPP2_UFCS(add_member)(t, "    operator<=>       : (this, that) -> std::strong_ordering;");
{
std::string to_string_impl{"    to_string_impl: (this, prefix: std::string_view"};

    //  Provide 'to_string' and 'to_code' functions to print enumerator
    //  name(s) as human-readable strings or as code expressions

#line 1171 "reflect.h2"
    {
        if (bitwise) {
            to_string_impl += ", separator: std::string_view ) -> std::string = { \n"
                              "    ret : std::string = \"(\";\n"
                              "    sep : std::string = ();\n"
                              "    if this == none { return \"(none)\"; }\n";
        }
        else {
            to_string_impl += ") -> std::string = { \n";
        }

        to_string_impl += "    pref := cpp2::to_string(prefix);\n";

        for ( 
              auto const& e : enumerators ) {
            if (e.name != "_") {// ignore unnamed values
                if (bitwise) {
                    if (e.name != "none") {
                        to_string_impl += "    if (this & " + cpp2::to_string(CPP2_UFCS(name)(t)) + "::" + cpp2::to_string(e.name) + ") == " + cpp2::to_string(CPP2_UFCS(name)(t)) + "::" + cpp2::to_string(e.name) + " { "
                                                  "ret += sep + pref + \"" + cpp2::to_string(e.name) + "\"; sep = separator; "
                                              "}\n";
                    }
                }
                else {
                    to_string_impl += "    if this == " + cpp2::to_string(CPP2_UFCS(name)(t)) + "::" + cpp2::to_string(e.name) + " { return pref + \"" + cpp2::to_string(e.name) + "\"; }\n";
                }
            }
        }

        if (bitwise) {
            to_string_impl += "    return ret+\")\";\n}\n";
        }
        else {
            to_string += "    return \"invalid " + cpp2::to_string(CPP2_UFCS_0(name, t)) + " value\";\n}\n";
        }

        CPP2_UFCS(add_member, t, std::move(to_string));
    }
}
#line 1203 "reflect.h2"
}

#line 1215 "reflect.h2"
auto cpp2_enum(meta::type_declaration& t) -> void
{
    //  Let basic_enum do its thing, with an incrementing value generator
    CPP2_UFCS(basic_enum, t, 
        [](std::string& value, cpp2::in<std::string> specified_value) mutable -> void{
            if (!(CPP2_UFCS_0(empty, specified_value))) {
                value = specified_value;
            }else {
                auto v {std::strtoll(&CPP2_ASSERT_IN_BOUNDS_LITERAL(value, 0), nullptr, 10)}; 
                value = cpp2::impl::as_<std::string>((cpp2::move(v) + 1));
            }
        }, 
        false   // disable bitwise operations
    );
}

#line 1242 "reflect.h2"
auto flag_enum(meta::type_declaration& t) -> void
{
    //  Let basic_enum do its thing, with a power-of-two value generator
    CPP2_UFCS(basic_enum, t, 
        [](std::string& value, cpp2::in<std::string> specified_value) mutable -> void{
            if (!(CPP2_UFCS_0(empty, specified_value))) {
                value = specified_value;
            }else {
                auto v {std::strtoll(&CPP2_ASSERT_IN_BOUNDS_LITERAL(value, 0), nullptr, 10)}; 
                if (cpp2::impl::cmp_less(v,1)) {
                    value = "1";
                }
                else {
                    value = cpp2::impl::as_<std::string>((cpp2::move(v) * 2));
                }
            }
        }, 
        true    // enable bitwise operations
    );
}

#line 1288 "reflect.h2"
auto cpp2_union(meta::type_declaration& t) -> void
{
    std::vector<value_member_info> alternatives {}; 
{
auto value{0};

    //  1. Gather: All the user-written members, and find/compute the max size

#line 1295 "reflect.h2"
    for ( 

           auto const& m : CPP2_UFCS_0(get_members, t) )  { do 
    if (   CPP2_UFCS_0(is_member_object, m)) 
    {
        CPP2_UFCS(require, m, CPP2_UFCS_0(is_public, m) || CPP2_UFCS_0(is_default_access, m), 
                   "a union alternative cannot be protected or private");

        CPP2_UFCS(require, m, !(CPP2_UFCS(starts_with, CPP2_UFCS_0(name, m), "is_")) 
                   && !(CPP2_UFCS(starts_with, CPP2_UFCS_0(name, m), "set_")), 
                   "a union alternative's name cannot start with 'is_' or 'set_' - that could cause user confusion with the 'is_alternative' and 'set_alternative' generated functions");

        auto mo {CPP2_UFCS_0(as_object, m)}; 
        CPP2_UFCS(require, mo, CPP2_UFCS_0(empty, CPP2_UFCS_0(initializer, mo)), 
                    "a union alternative cannot have an initializer");

        //  Adding local variable 'e' to work around a Clang warning
        value_member_info e {cpp2::as_<std::string>(CPP2_UFCS_0(name, mo)), CPP2_UFCS_0(type, mo), cpp2::as_<std::string>(value)}; 
        CPP2_UFCS(push_back, alternatives, e);

        CPP2_UFCS_0(mark_for_removal_from_enclosing_type, mo);
    } while (false); ++value; }
}

#line 1323 "reflect.h2"
    std::string discriminator_type {}; 
    if (cpp2::cmp_less(CPP2_UFCS_0(ssize, alternatives),std::numeric_limits<cpp2::i8>::max())) {
        discriminator_type = "i8";
    }
    else {if (cpp2::cmp_less(CPP2_UFCS_0(ssize, alternatives),std::numeric_limits<cpp2::i16>::max())) {
        discriminator_type = "i16";
    }
    else {if (cpp2::cmp_less(CPP2_UFCS_0(ssize, alternatives),std::numeric_limits<cpp2::i32>::max())) {
        discriminator_type = "i32";
    }
    else {
        discriminator_type = "i64";
    }}}

#line 1338 "reflect.h2"
    //  2. Replace: Erase the contents and replace with modified contents

    CPP2_UFCS_0(remove_marked_members, t);
{
std::string storage{"    _storage: cpp2::aligned_storage<cpp2::max( "};

    //  Provide storage

#line 1344 "reflect.h2"
    {
        for ( 
              auto const& e : alternatives ) {
            storage += "sizeof(" + cpp2::to_string(e.type) + "), ";
        }

        storage += "), cpp2::max( ";

        for ( 
              auto const& e : alternatives ) {
            storage += "alignof(" + cpp2::to_string(e.type) + "), ";
        }

        storage += " )> = ();\n";
        CPP2_UFCS(add_member, t, std::move(storage));
    }
}

    //  Provide discriminator
#line 1167 "reflect.h2"
    CPP2_UFCS(add_member, t, "    _discriminator: " + cpp2::to_string(std::move(discriminator_type)) + " = -1;\n");

    //  Add the alternatives: is_alternative, get_alternative, and set_alternative
    for ( 
         auto const& a : alternatives ) 
    {
        CPP2_UFCS(add_member, t, "    is_" + cpp2::to_string(a.name) + ": (this) -> bool = _discriminator == " + cpp2::to_string(a.value) + ";\n");

        CPP2_UFCS(add_member, t, "    " + cpp2::to_string(a.name) + ": (this) -> forward " + cpp2::to_string(a.type) + " pre(is_" + cpp2::to_string(a.name) + "()) = reinterpret_cast<* const " + cpp2::to_string(a.type) + ">(_storage&)*;\n");

        CPP2_UFCS(add_member, t, "    " + cpp2::to_string(a.name) + ": (inout this) -> forward " + cpp2::to_string(a.type) + " pre(is_" + cpp2::to_string(a.name) + "()) = reinterpret_cast<*" + cpp2::to_string(a.type) + ">(_storage&)*;\n");

        CPP2_UFCS(add_member, t, "    set_" + cpp2::to_string(a.name) + ": (inout this, _value: " + cpp2::to_string(a.type) + ") = { if !is_" + cpp2::to_string(a.name) + "() { _destroy(); std::construct_at( reinterpret_cast<*" + cpp2::to_string(a.type) + ">(_storage&), _value); } else { reinterpret_cast<*" + cpp2::to_string(a.type) + ">(_storage&)* = _value; } _discriminator = " + cpp2::to_string(a.value) + "; }\n");

        CPP2_UFCS(add_member, t, "    set_" + cpp2::to_string(a.name) + ": (inout this, forward _args...: _) = { if !is_" + cpp2::to_string(a.name) + "() { _destroy(); std::construct_at( reinterpret_cast<*" + cpp2::to_string(a.type) + ">(_storage&), _args...); } else { reinterpret_cast<*" + cpp2::to_string(a.type) + ">(_storage&)* = :" + cpp2::to_string(a.type) + " = (_args...); } _discriminator = " + cpp2::to_string(a.value) + "; }\n");
    }
{
std::string destroy{"    private _destroy: (inout this) = {\n"};

    //  Add destroy

#line 1395 "reflect.h2"
    {
        for ( 
              auto const& a : alternatives ) {
            destroy += "        if _discriminator == " + cpp2::to_string(a.value) + " { std::destroy_at( reinterpret_cast<*" + cpp2::to_string(a.type) + ">(_storage&) ); }\n";
        }

        destroy += "        _discriminator = -1;\n";
        destroy += "    }\n";
        CPP2_UFCS(add_member, t, std::move(destroy));
    }
}

    //  Add the destructor
#line 1198 "reflect.h2"
    CPP2_UFCS(add_member, t, "    operator=: (move this) = { _destroy(); }");

    //  Add default constructor
    CPP2_UFCS(add_member, t, "    operator=: (out this) = { }");
{
std::string value_set{""};

    //  Add copy/move construction and assignment

#line 1414 "reflect.h2"
    {
        for ( 
              auto const& a : cpp2::move(alternatives) ) {
            value_set += "        if that.is_" + cpp2::to_string(a.name) + "() { set_" + cpp2::to_string(a.name) + "( that." + cpp2::to_string(a.name) + "() ); }\n";
        }
        value_set += "    }\n";

        CPP2_UFCS(add_member, t, std::string("    operator=: (out this, that) = {\n") 
                    + "        _storage = ();\n" 
                    + "        _discriminator = -1;\n" 
                    + value_set
                    );
        CPP2_UFCS(add_member, t, std::string("    operator=: (inout this, that) = {\n") 
                    + "        _storage = _;\n" 
                    + "        _discriminator = _;\n" 
                    + std::move(value_set)
                    );
    }
}
#line 1432 "reflect.h2"
}

#line 1439 "reflect.h2"
auto print(cpp2::impl::in<meta::type_declaration> t) -> void
{
    std::cout << CPP2_UFCS_0(print, t) << "\n";
}

#line 1449 "reflect.h2"
[[nodiscard]] auto apply_metafunctions(
    declaration_node& n, 
    type_declaration& rtype, 
    auto const& error
    ) -> bool

{
    cpp2::Default.expects(CPP2_UFCS_0(is_type, n), "");

    //  Check for _names reserved for the metafunction implementation
    for ( 
          auto const& m : CPP2_UFCS_0(get_members, rtype) ) 
    {
        CPP2_UFCS(require, m, !(CPP2_UFCS(starts_with, CPP2_UFCS_0(name, m), "_")) || cpp2::cmp_greater(CPP2_UFCS_0(ssize, CPP2_UFCS_0(name, m)),1), 
                    "a type that applies a metafunction cannot have a body that declares a name that starts with '_' - those names are reserved for the metafunction implementation");
    }

    //  For each metafunction, apply it
    for ( 
         auto const& meta : n.metafunctions ) 
    {
        //  Convert the name and any template arguments to strings
        //  and record that in rtype
        auto name {CPP2_UFCS_0(to_string, (*cpp2::assert_not_null(meta)))}; 
        name = CPP2_UFCS(substr, name, 0, CPP2_UFCS(find, name, '<'));

        std::vector<std::string> args {}; 
        for ( 
             auto const& arg : CPP2_UFCS_0(template_arguments, (*cpp2::assert_not_null(meta))) ) 
            CPP2_UFCS(push_back, args, CPP2_UFCS_0(to_string, arg));

        CPP2_UFCS(set_metafunction_name, rtype, name, args);

        //  Dispatch
        //
        if (name == "interface") {
            interface(rtype);
        }
        else {if (name == "polymorphic_base") {
            polymorphic_base(rtype);
        }
        else {if (name == "ordered") {
            ordered(rtype);
        }
        else {if (name == "weakly_ordered") {
            weakly_ordered(rtype);
        }
        else {if (name == "partially_ordered") {
            partially_ordered(rtype);
        }
        else {if (name == "copyable") {
            copyable(rtype);
        }
        else {if (name == "copy_constructible") {
            copy_constructible(rtype);
        }
        else {if (name == "hashable") {
            hashable(rtype);
        }
        else {if (name == "basic_value") {
            basic_value(rtype);
        }
        else {if (name == "value") {
            value(rtype);
        }
        else {if (name == "weakly_ordered_value") {
            weakly_ordered_value(rtype);
        }
        else {if (name == "partially_ordered_value") {
            partially_ordered_value(rtype);
        }
        else {if (name == "cpp1_rule_of_zero") {
            cpp1_rule_of_zero(rtype);
        }
        else {if (name == "struct") {
            cpp2_struct(rtype);
        }
        else {if (name == "enum") {
            cpp2_enum(rtype);
        }
        else {if (name == "flag_enum") {
            flag_enum(rtype);
        }
        else {if (name == "union") {
            cpp2_union(rtype);
        }
        else {if (name == "encapsulated") {
            encapsulated(rtype);
        }
        else {if (name == "noncopyable") {
            noncopyable(rtype);
        }
        else {if (name == "singleton") {
            singleton(rtype);
        }
        else {if (name == "print") {
            print(rtype);
        }
        else {
            error("unrecognized metafunction name: " + cpp2::move(name));
            error(
                "(temporary alpha limitation) currently the supported names are: "
                "interface, polymorphic_base, ordered, weakly_ordered, partially_ordered, "
                "copyable, basic_value, value, weakly_ordered_value, partially_ordered_value, "
                "struct, enum, flag_enum, union, cpp1_rule_of_zero, print"
            );
            return false; 
        }}}}}}}}}}}}}}}}

        if ((
            !(CPP2_UFCS_0(empty, args)) 
            && !(CPP2_UFCS_0(arguments_were_used, rtype)))) 

        {
            error(name + " did not use its template arguments - did you mean to write '" + name + " <" + CPP2_ASSERT_IN_BOUNDS_LITERAL(cpp2::move(args), 0) + "> type' (with the spaces)?");
            return false; 
        }
    }

    return true; 
}

#line 1561 "reflect.h2"
}

}

#endif
