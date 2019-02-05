// For a quick way to extend the default keywords:
// #define FCPP_LEXER_EXTRA_KEYWORDS "my_keywords.h"
// And in the file "my_keywords.h", list the keywords you want.

// For a quick way to extend the default preprocessor 
// directives do the same thing with the macro:
// #define FCPP_LEXER_EXTRA_PREPROPS

// TOP

#if !defined(FCPP_DEFAULT_KEYWORDS_H)
#define FCPP_DEFAULT_KEYWORDS_H

#define make_stafl(s,f) (s), sizeof(s)-1, f

struct String_And_Flag{
    char *str;
    u32_4tech length;
    u32_4tech flags;
};

static String_And_Flag default_preprops[] = {
    {make_stafl("include" , CPP_PP_INCLUDE )} ,
    {make_stafl("INCLUDE" , CPP_PP_INCLUDE )} ,
    {make_stafl("version" , CPP_PP_VERSION )} ,
    {make_stafl("VERSION" , CPP_PP_VERSION )} ,
    {make_stafl("ifndef"  , CPP_PP_IFNDEF  )} ,
    {make_stafl("IFNDEF"  , CPP_PP_IFNDEF  )} ,
    {make_stafl("define"  , CPP_PP_DEFINE  )} ,
    {make_stafl("DEFINE"  , CPP_PP_DEFINE  )} ,
    {make_stafl("import"  , CPP_PP_IMPORT  )} ,
    {make_stafl("IMPORT"  , CPP_PP_IMPORT  )} ,
    {make_stafl("pragma"  , CPP_PP_PRAGMA  )} ,
    {make_stafl("PRAGMA"  , CPP_PP_PRAGMA  )} ,
    {make_stafl("undef"   , CPP_PP_UNDEF   )} ,
    {make_stafl("UNDEF"   , CPP_PP_UNDEF   )} ,
    {make_stafl("endif"   , CPP_PP_ENDIF   )} ,
    {make_stafl("ENDIF"   , CPP_PP_ENDIF   )} ,
    {make_stafl("error"   , CPP_PP_ERROR   )} ,
    {make_stafl("ERROR"   , CPP_PP_ERROR   )} ,
    {make_stafl("ifdef"   , CPP_PP_IFDEF   )} ,
    {make_stafl("IFDEF"   , CPP_PP_IFDEF   )} ,
    {make_stafl("using"   , CPP_PP_USING   )} ,
    {make_stafl("USING"   , CPP_PP_USING   )} ,
    {make_stafl("else"    , CPP_PP_ELSE    )} ,
    {make_stafl("ELSE"    , CPP_PP_ELSE    )} ,
    {make_stafl("elif"    , CPP_PP_ELIF    )} ,
    {make_stafl("ELIF"    , CPP_PP_ELIF    )} ,
    {make_stafl("line"    , CPP_PP_LINE    )} ,
    {make_stafl("LINE"    , CPP_PP_LINE    )} ,
    {make_stafl("if"      , CPP_PP_IF      )} ,
    {make_stafl("IF"      , CPP_PP_IF      )} ,
    
#if defined(FCPP_LEXER_EXTRA_PREPROPS)
#include FCPP_LEXER_EXTRA_PREPROPS
#endif
};
static i32_4tech default_preprops_count = sizeof(default_preprops)/sizeof(default_preprops[0]);

static String_And_Flag default_keywords[] = {
    // CPP_TOKEN_BOOLEAN_CONSTANT
    {make_stafl("true"  , CPP_TOKEN_TRUE)},
    {make_stafl("false" , CPP_TOKEN_FALSE)},
    
    // CPP_TOKEN_KEY_OPERATOR
    {make_stafl("and"      , CPP_TOKEN_AND)},
    {make_stafl("and_eq"   , CPP_TOKEN_ANDEQ)},
    {make_stafl("bitand"   , CPP_TOKEN_BIT_AND)},
    {make_stafl("bitor"    , CPP_TOKEN_BIT_OR)},
    {make_stafl("or"       , CPP_TOKEN_OR)},
    {make_stafl("or_eq"    , CPP_TOKEN_OREQ)},
    {make_stafl("sizeof"   , CPP_TOKEN_SIZEOF)},
    {make_stafl("alignof"  , CPP_TOKEN_ALIGNOF)},
    {make_stafl("decltype" , CPP_TOKEN_DECLTYPE)},
    {make_stafl("throw"    , CPP_TOKEN_THROW)},
    {make_stafl("new"      , CPP_TOKEN_NEW)},
    {make_stafl("delete"   , CPP_TOKEN_DELETE)},
    {make_stafl("xor"      , CPP_TOKEN_BIT_XOR)},
    {make_stafl("xor_eq"   , CPP_TOKEN_XOREQ)},
    {make_stafl("not"      , CPP_TOKEN_NOT)},
    {make_stafl("not_eq"   , CPP_TOKEN_NOTEQ)},
    {make_stafl("typeid"   , CPP_TOKEN_TYPEID)},
    {make_stafl("compl"    , CPP_TOKEN_BIT_NOT)},
    
    // CPP_TOKEN_KEY_TYPE
    {make_stafl("void"   , CPP_TOKEN_VOID)},
    {make_stafl("bool"   , CPP_TOKEN_BOOL)},
    {make_stafl("char"   , CPP_TOKEN_CHAR)},
    {make_stafl("int"    , CPP_TOKEN_INT)},
    {make_stafl("float"  , CPP_TOKEN_FLOAT)},
    {make_stafl("double" , CPP_TOKEN_DOUBLE)},
    
    // CPP_TOKEN_KEY_MODIFIER
    {make_stafl("long"     , CPP_TOKEN_LONG)},
    {make_stafl("short"    , CPP_TOKEN_SHORT)},
    {make_stafl("unsigned" , CPP_TOKEN_UNSIGNED)},
    {make_stafl("signed"   , CPP_TOKEN_SIGNED)},
    
    // CPP_TOKEN_KEY_QUALIFIER
    {make_stafl("const"    , CPP_TOKEN_CONST)},
    {make_stafl("volatile" , CPP_TOKEN_VOLATILE)},
    
    // CPP_TOKEN_KEY_CONTROL_FLOW
    {make_stafl("asm"           , CPP_TOKEN_ASM)},
    {make_stafl("break"         , CPP_TOKEN_BREAK)},
    {make_stafl("case"          , CPP_TOKEN_CASE)},
    {make_stafl("catch"         , CPP_TOKEN_CATCH)},
    {make_stafl("continue"      , CPP_TOKEN_CONTINUE)},
    {make_stafl("default"       , CPP_TOKEN_DEFAULT)},
    {make_stafl("do"            , CPP_TOKEN_DO)},
    {make_stafl("else"          , CPP_TOKEN_ELSE)},
    {make_stafl("for"           , CPP_TOKEN_FOR)},
    {make_stafl("goto"          , CPP_TOKEN_GOTO)},
    {make_stafl("if"            , CPP_TOKEN_IF)},
    {make_stafl("return"        , CPP_TOKEN_RETURN)},
    {make_stafl("switch"        , CPP_TOKEN_SWITCH)},
    {make_stafl("try"           , CPP_TOKEN_TRY)},
    {make_stafl("while"         , CPP_TOKEN_WHILE)},
    {make_stafl("static_assert" , CPP_TOKEN_STATIC_ASSERT)},
    
    // CPP_TOKEN_KEY_CAST
    {make_stafl("const_cast"       , CPP_TOKEN_CONST_CAST)},
    {make_stafl("dynamic_cast"     , CPP_TOKEN_DYNAMIC_CAST)},
    {make_stafl("reinterpret_cast" , CPP_TOKEN_REINTERPRET_CAST)},
    {make_stafl("static_cast"      , CPP_TOKEN_STATIC_CAST)},
    
    // CPP_TOKEN_KEY_TYPE_DECLARATION
    {make_stafl("class"    , CPP_TOKEN_CLASS)},
    {make_stafl("enum"     , CPP_TOKEN_ENUM)},
    {make_stafl("struct"   , CPP_TOKEN_STRUCT)},
    {make_stafl("typedef"  , CPP_TOKEN_TYPEDEF)},
    {make_stafl("union"    , CPP_TOKEN_UNION)},
    {make_stafl("template" , CPP_TOKEN_TEMPLATE)},
    {make_stafl("typename" , CPP_TOKEN_TYPENAME)},
    
    // CPP_TOKEN_KEY_ACCESS
    {make_stafl("friend"    , CPP_TOKEN_FRIEND)},
    {make_stafl("namespace" , CPP_TOKEN_NAMESPACE)},
    {make_stafl("private"   , CPP_TOKEN_PRIVATE)},
    {make_stafl("protected" , CPP_TOKEN_PROTECTED)},
    {make_stafl("public"    , CPP_TOKEN_PUBLIC)},
    {make_stafl("using"     , CPP_TOKEN_USING)},
    
    // CPP_TOKEN_KEY_LINKAGE
    {make_stafl("extern"  , CPP_TOKEN_EXTERN)},
    {make_stafl("export"  , CPP_TOKEN_EXPORT)},
    {make_stafl("inline"  , CPP_TOKEN_INLINE)},
    {make_stafl("static"  , CPP_TOKEN_STATIC)},
    {make_stafl("virtual" , CPP_TOKEN_VIRTUAL)},
    
    // CPP_TOKEN_KEY_OTHER
    {make_stafl("alignas"      , CPP_TOKEN_ALIGNAS)},
    {make_stafl("explicit"     , CPP_TOKEN_EXPLICIT)},
    {make_stafl("noexcept"     , CPP_TOKEN_NOEXCEPT)},
    {make_stafl("nullptr"      , CPP_TOKEN_NULLPTR)},
    {make_stafl("operator"     , CPP_TOKEN_OPERATOR)},
    {make_stafl("register"     , CPP_TOKEN_REGISTER)},
    {make_stafl("this"         , CPP_TOKEN_THIS)},
    {make_stafl("thread_local" , CPP_TOKEN_THREAD_LOCAL)},
    
#if defined(FCPP_LEXER_EXTRA_KEYWORDS)
#include FCPP_LEXER_EXTRA_KEYWORDS
#endif
};
static i32_4tech default_keywords_count = sizeof(default_keywords)/sizeof(default_keywords[0]);

#endif

// BOTTOM

