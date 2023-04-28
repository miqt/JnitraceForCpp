//
// Created by zhenxi on 2022/2/6.
//

#include "../includes/invokePrintf.h"

#include "HookUtils.h"
#include "AllInclude.h"
#include "ZhenxiLog.h"
#include "logging.h"
#include "libpath.h"
#include "version.h"
#include "xdl.h"
#include "adapter.h"


static std::ofstream *invokeOs;
static bool isSave = false;

std::string (*invokePrintf_org_PrettyMethodSym)(void *thiz, bool b) = nullptr;

HOOK_DEF(void*, invoke, void *thiz, void *self, uint32_t *args, uint32_t args_size, void *result,
         const char *shorty) {

    string basicString = invokePrintf_org_PrettyMethodSym(thiz, true);

    LOG(INFO) << "invoke method info -> " << basicString;

    if (isSave) {
        *invokeOs << basicString.append("\n");
    }
    return orig_invoke(thiz, self, args, args_size, result, shorty);
}

__always_inline
static string getFileNameForPath(const char *path) {
    std::string pathStr = path;
    size_t pos = pathStr.rfind('/');
    if (pos != std::string::npos) {
        return pathStr.substr(pos + 1);
    }
    return pathStr;
}

void invokePrintf::HookJNIInvoke(JNIEnv *env,
                                 std::ofstream *os,
                                 std::string(*prettyMethodSym)(void *, bool)) {
    if (os != nullptr) {
        invokeOs = os;
        isSave = true;
    }
    if (invokePrintf_org_PrettyMethodSym == nullptr) {
        invokePrintf_org_PrettyMethodSym = prettyMethodSym;
    }
    if (invokePrintf_org_PrettyMethodSym == nullptr) {
        LOGE(">>>>>>>>>>>>>> HookJNIInvoke PrettyMethodSym == null ")
        return;
    }
    //artmethod->invoke
    void *invokeSym = getSymCompat(getlibArtPath(),
                                   "_ZN3art9ArtMethod6InvokeEPNS_6ThreadEPjjPNS_6JValueEPKc");
    if (invokeSym == nullptr) {
        LOGE(">>>>>>>>> hook art method invoke fail ")
        return;
    }
    bool isSuccess = HookUtils::Hooker(invokeSym,
                                       (void *) new_invoke,
                                       (void **) &orig_invoke);
    LOGE(">>>>>>>>> hook art method invoke success ! %s ", isSuccess ? "true" : "false")
}

void RegisterNativeCallBack(void *method, const void *native_method) {
    if (method == nullptr || native_method == nullptr) {
        return;
    }
    string basicString = invokePrintf_org_PrettyMethodSym(method, true);
    if (isSave) {
        *invokeOs << basicString.append("\n");
    }
    Dl_info info;
    dladdr(native_method, &info);
    size_t relative_offset =
            reinterpret_cast<size_t>(native_method) - reinterpret_cast<size_t>(info.dli_fbase);

    LOG(INFO) << "REGISTER_NATIVE " << basicString.c_str() << " absolute address(内存地址)["
              << native_method << "]  relative offset(相对地址) [" << (void *) relative_offset
              << "]  所属ELF文件[" << getFileNameForPath(info.dli_fname) + "]";
}


//12以上
//const void* RegisterNative(Thread* self, ArtMethod* method, const void* native_method)
HOOK_DEF(void*, RegisterNative_12, void *self, void *method, const void *native_method) {
    RegisterNativeCallBack(method, native_method);
    return orig_RegisterNative_12(self, method, native_method);
}
//11
HOOK_DEF(void*, RegisterNative_11, void *method, const void *native_method) {
    RegisterNativeCallBack(method, native_method);
    return orig_RegisterNative_11(method, native_method);
}

HOOK_DEF(void*, RegisterNative, void *method, const void *native_method, bool b) {
    RegisterNativeCallBack(method, native_method);
    return orig_RegisterNative(method, native_method,b);
}


void invokePrintf::HookJNIRegisterNative(JNIEnv *env,
                                         std::ofstream *os,
                                         std::string(*prettyMethodSym)(void *, bool)) {
    if (os != nullptr) {
        invokeOs = os;
        isSave = true;
    }
    if (invokePrintf_org_PrettyMethodSym == nullptr) {
        invokePrintf_org_PrettyMethodSym = prettyMethodSym;
    }
    if (invokePrintf_org_PrettyMethodSym == nullptr) {
        LOGE(">>>>>>>>>>>>>> HookJNIRegisterNative PrettyMethodSym == null ")
        return;
    }
    void *art_method_register;
    if (get_sdk_level() < ANDROID_S) {
        //android 11
        art_method_register = getSymCompat(getlibArtPath(),
                                           "_ZN3art9ArtMethod14RegisterNativeEPKv");
        if (art_method_register == nullptr) {
            art_method_register = getSymCompat(getlibArtPath(),
                                               "_ZN3art9ArtMethod14RegisterNativeEPKvb");
        }
    } else {
        //12以上
        art_method_register = getSymCompat(getlibArtPath(),
                                           "_ZN3art11ClassLinker14RegisterNativeEPNS_6ThreadEPNS_9ArtMethodEPKv");
    }

    if (art_method_register == nullptr) {
        LOGE(">>>>>>>>> hook art method invoke fail ")
        return;
    }
    bool isSuccess;
    if (get_sdk_level() >= ANDROID_S) {
        isSuccess = HookUtils::Hooker(art_method_register,
                                      (void *) new_RegisterNative_12,
                                      (void **) &orig_RegisterNative_12);
    } else if (get_sdk_level() >= ANDROID_R) {
        isSuccess = HookUtils::Hooker(art_method_register,
                                      (void *) new_RegisterNative_11,
                                      (void **) &orig_RegisterNative_11);
    } else {
        isSuccess = HookUtils::Hooker(art_method_register,
                                      (void *) new_RegisterNative,
                                      (void **) &orig_RegisterNative);
    }
    LOGE(">>>>>>>>> hook art method register nativeS success ! %s ", isSuccess ? "true" : "false")
}