#pragma once
#include "platform.h"

#if defined(_MSC_VER)
#define __V8VM_DECLSPEC_EXPORT  __declspec(dllexport)
#define __V8VM_DECLSPEC_IMPORT  __declspec(dllimport)
#define V8VM_STDCALL __stdcall
#else
#define __V8VM_DECLSPEC_EXPORT  
#define __V8VM_DECLSPEC_IMPORT
#define V8VM_STDCALL 
//#define V8VM_STDCALL __attribute__((__stdcall__))
#endif


#ifdef LIBV8VM
#define V8VM_EXTERN  __V8VM_DECLSPEC_EXPORT
#else
#define V8VM_EXTERN  __V8VM_DECLSPEC_IMPORT
#endif

#ifdef __cplusplus
extern "C" {
#endif
    V8VM_EXTERN void V8VM_STDCALL SetInternalJSLibPath(const char* path);
    V8VM_EXTERN void V8VM_STDCALL SetJSSourcePath(const char* path);

    V8VM_EXTERN Int64 V8VM_STDCALL NewString(const char* str);
    V8VM_EXTERN void V8VM_STDCALL DeleteString(Int64 ptr);


    V8VM_EXTERN void V8VM_STDCALL InitializeV8Environment();
    V8VM_EXTERN void V8VM_STDCALL ShutdownV8Environment();
    V8VM_EXTERN Int64 V8VM_STDCALL CreateV8VirtualMation(Int64 expected_vmid);
    V8VM_EXTERN void V8VM_STDCALL DisposeV8VirtualMation(Int64 vmid);
    V8VM_EXTERN bool V8VM_STDCALL IsV8VirtualMationInUse(Int64 vmid);
    V8VM_EXTERN bool V8VM_STDCALL IsSmartContractLoaded(Int64 vmid, const char* contract_name);
    V8VM_EXTERN int V8VM_STDCALL LoadSmartContractBySourcecode(Int64 vmid, const char* contract_name, const char* sourcecode);
    V8VM_EXTERN int V8VM_STDCALL LoadSmartContractByFileName(Int64 vmid, const char* contract_name, const char* filename);
    //返回js脚本的返回值：0表示正常；<=-10000是V8VM_ERROR
    V8VM_EXTERN int V8VM_STDCALL InvokeSmartContract(Int64 vmid, const char* contract_name, int param1, const char* param2);

    typedef void(*Log_callback)(Int64 vmid, Int32 level, char* text);
    V8VM_EXTERN void V8VM_STDCALL SetLog(Log_callback fn);

    typedef int(*BalanceTransfer_callback)(Int64 vmid, char* from, char* to, char* amount);
    V8VM_EXTERN void V8VM_STDCALL SetBalanceTransfer(BalanceTransfer_callback fn);

    typedef int(*UpdateDB_callback)(Int64 vmid, char* key_json, char* value_json);
    V8VM_EXTERN void V8VM_STDCALL SetUpdateDB(UpdateDB_callback fn);

    typedef Int64(*QueryDB_callback)(Int64 vmid, char* key_json);
    V8VM_EXTERN void V8VM_STDCALL SetQueryDB(QueryDB_callback fn);

    typedef int(*RequireAuth_callback)(Int64 vmid, char* account);
    V8VM_EXTERN void V8VM_STDCALL SetRequireAuth(RequireAuth_callback fn);

    typedef int(*GetIntValue_callback)(Int64 vmid, Int32 keyid);
    typedef Int64(*GetStringValue_callback)(Int64 vmid, Int32 keyid);
    V8VM_EXTERN void V8VM_STDCALL SetValueGetter(GetIntValue_callback fn1, GetStringValue_callback fn2);

#ifdef __cplusplus
}
#endif


//此处都定义为<=-10000的值.
#define V8VM_SUCCESS                    0
#define V8VM_ERROR_ENVIRONMENT          (-10000)
#define V8VM_ERROR_INVALID_VMID         (-10001)
#define V8VM_ERROR_INVALID_CONTRACT     (-10002)
#define V8VM_ERROR_CONTRACT_EXISTS      (-10003)
#define V8VM_ERROR_SOURCECODE_EXISTS    (-10004)
#define V8VM_ERROR_LOAD_CONTRACT        (-10004)
