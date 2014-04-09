#ifndef _H_DEFINITION
#define _H_DEFINITION

#include "platform/tlibc_platform.h"
#include <stdint.h>


#define MAX_COMMENT_LENGTH 1024
typedef struct syn_unix_comment_s
{
    char text[MAX_COMMENT_LENGTH];
}syn_unix_comment_t;


typedef enum syn_value_type_e
{
    E_SNVT_IDENTIFIER = 0,
    E_SNVT_CHAR = 1,
    E_SNVT_DOUBLE = 2,
    E_SNVT_STRING = 3,
    E_SNVT_INT64 = 4,
    E_SNVT_UINT64 = 5,
    E_SNVT_HEX_INT64 = 6,
    E_SNVT_HEX_UINT64 = 7,
}syn_value_type_t;


typedef union syn_value_body_u
{
    int64_t i64;
    uint64_t ui64;
    char str[TLIBC_MAX_LENGTH_OF_IDENTIFIER];
    double d;
    char c;
    char identifier[TLIBC_MAX_LENGTH_OF_IDENTIFIER];//const, enumdef
}syn_value_body_t;

typedef struct  syn_value_s
{
    syn_value_type_t type;
    syn_value_body_t val;
}syn_value_t;

typedef enum syn_type_type_e
{
	E_SNT_SIMPLE = 0,
	E_SNT_CONTAINER = 1,
}syn_type_type_t;

typedef enum syn_simple_type_type_e
{
    E_ST_INT8 = 0,
    E_ST_INT16 = 1,
    E_ST_INT32 = 2,
    E_ST_INT64 = 3,
    E_ST_UINT8 = 4,
    E_ST_UINT16 = 5,
    E_ST_UINT32 = 6,
    E_ST_UINT64 = 7,    
    E_ST_CHAR = 8,
    E_ST_DOUBLE = 9,
	E_ST_STRING = 10,
	E_ST_REFER = 11,//struct, union, enum, typedef
}syn_simple_type_type_t;
typedef struct syn_simple_type_s
{
	syn_simple_type_type_t st;
	
	char string_length[TLIBC_MAX_LENGTH_OF_IDENTIFIER];

	char st_refer[TLIBC_MAX_LENGTH_OF_IDENTIFIER];
}syn_simple_type_t;

typedef enum syn_container_type_type_e
{
	E_CT_VECTOR = 0,
}syn_container_type_type_t;
typedef struct syn_container_type_s
{
	syn_container_type_type_t ct;

	syn_simple_type_t vector_type;
	char vector_length[TLIBC_MAX_LENGTH_OF_IDENTIFIER];
}syn_container_type_t;

typedef struct  _ST_TYPE
{
    syn_type_type_t type;
    
	syn_simple_type_t st;

	syn_container_type_t ct;	
}ST_TYPE;
typedef struct  _ST_Parameter
{
    syn_simple_type_t type;
    char identifier[TLIBC_MAX_LENGTH_OF_IDENTIFIER];
}ST_Parameter;
#define MAX_PARAMETER_NUM 1
typedef struct  _ST_Parameters
{
	uint32_t par_list_num;
    ST_Parameter par_list[MAX_PARAMETER_NUM];
}ST_Parameters;
#define MAX_ARGUMENT_NUM 1
typedef struct  _ST_ARGUMENTS
{
	uint32_t arg_list_num;
    char arg_list[MAX_ARGUMENT_NUM][TLIBC_MAX_LENGTH_OF_IDENTIFIER];
}ST_ARGUMENTS;
typedef enum _ST_EXPRESSION_OPER
{
	E_EO_NON = 0,
    E_EO_AND = 2,
    E_EO_EQUAL = 3,
	E_EO_UNEQUAL = 4,
}ST_EXPRESSION_OPER;
typedef struct  _ST_CONDITION
{
	ST_EXPRESSION_OPER oper;
	char op0[TLIBC_MAX_LENGTH_OF_IDENTIFIER];
	syn_value_t op1;
}ST_CONDITION;
typedef struct  _ST_FIELD
{
    ST_CONDITION condition;
    ST_TYPE type;    
    char identifier[TLIBC_MAX_LENGTH_OF_IDENTIFIER];
	ST_ARGUMENTS args;
    syn_unix_comment_t comment;
}ST_FIELD;


typedef struct  _ST_UNION_FIELD
{
	char key[TLIBC_MAX_LENGTH_OF_IDENTIFIER];
	syn_simple_type_t simple_type;
	char name[TLIBC_MAX_LENGTH_OF_IDENTIFIER];
	syn_unix_comment_t comment;
}ST_UNION_FIELD;
#define MAX_UNION_FIELD_LIST_NUM 65536
typedef struct  _ST_UNION_FIELD_LIST
{
	uint32_t union_field_list_num;
	ST_UNION_FIELD union_field_list[MAX_UNION_FIELD_LIST_NUM];
}ST_UNION_FIELD_LIST;


#define MAX_PACKAGE_NAME_LENGTH 1024
typedef struct  _ST_Import
{
    char package_name[MAX_PACKAGE_NAME_LENGTH];
}ST_Import;
typedef struct  _ST_Const
{
    syn_simple_type_t type;
    char identifier[TLIBC_MAX_LENGTH_OF_IDENTIFIER];
    syn_value_t val;
}ST_Const;
typedef struct  _ST_ENUM_DEF
{
    char identifier[TLIBC_MAX_LENGTH_OF_IDENTIFIER];
    syn_value_t val;
    syn_unix_comment_t comment;
}ST_ENUM_DEF;
#define MAX_ENUM_DEF_LIST_NUM 65536
typedef struct  _ST_ENUM
{
    char name[TLIBC_MAX_LENGTH_OF_IDENTIFIER];
	uint32_t enum_def_list_num;
    ST_ENUM_DEF enum_def_list[MAX_ENUM_DEF_LIST_NUM];
}ST_ENUM;
#define MAX_FIELD_LIST_NUM 65536
typedef struct  _ST_FIELD_LIST
{
	uint32_t field_list_num;
    ST_FIELD field_list[MAX_FIELD_LIST_NUM];
}ST_FIELD_LIST;
typedef struct  _ST_STRUCT
{
    char name[TLIBC_MAX_LENGTH_OF_IDENTIFIER];
    ST_FIELD_LIST field_list;
}ST_STRUCT;
typedef struct  _ST_UNION
{
    char name[TLIBC_MAX_LENGTH_OF_IDENTIFIER];
    ST_Parameters parameters;
    ST_UNION_FIELD_LIST union_field_list;
}ST_UNION;
typedef struct  _ST_TYPEDEF
{
    syn_simple_type_t type;
    char name[TLIBC_MAX_LENGTH_OF_IDENTIFIER];
}ST_TYPEDEF;
typedef enum _EN_DEFINITION_TYPE
{
    E_DT_IMPORT = 0,
    E_DT_CONST = 1,
    E_DT_ENUM = 2,
    E_DT_STRUCT = 3,
    E_DT_UNION = 4,
    E_DT_TYPEDEF = 5,
    E_DT_UNIX_COMMENT = 6,
}EN_DEFINITION_TYPE;
typedef union  _UN_DEFINITION
{
    ST_Import de_import;
    ST_Const de_const;
    syn_unix_comment_t de_unix_comment;
    ST_ENUM de_enum;
    ST_STRUCT de_struct;
    ST_UNION de_union;
    ST_TYPEDEF de_typedef;
}UN_DEFINITION;
typedef struct  _ST_DEFINITION
{
    EN_DEFINITION_TYPE type;
    UN_DEFINITION definition;
}ST_DEFINITION;
#endif//_H_DEFINITION
