#pragma once

#include <map>
#include "libplatform/libplatform.h"
#include "v8.h"
#include "platform.h"

#define SMART_CONTRACT_OWN_SEPERATE_CONTEXT 0

#define SMART_CONTRACT_PROCESS "Process"
#define INVOKE_PARAM_PARAM0 "param0"
#define INVOKE_PARAM_PARAM1 "param1"
#define INVOKE_PARAM_PARAM2 "param2"

class V8VirtualMation;

struct InvokeParam
{
    int param0;         //Reserved
    int param1;         //整数参数
    std::string param2; //字符串参数，json
};

class SmartContract
{
public:
    explicit SmartContract(V8VirtualMation* vm);
    ~SmartContract();
    bool InitializeByFileName(const char* filename);
    int Invoke(InvokeParam* param);

private:
    V8VirtualMation* m_vm;
#if SMART_CONTRACT_OWN_SEPERATE_CONTEXT
    v8::Global<v8::Context> m_context;
    std::map<std::string, std::string> m_output;
#endif
    v8::Global<v8::Function> m_process_fun;
};
