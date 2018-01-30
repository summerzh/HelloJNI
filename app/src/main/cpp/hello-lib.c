#include <jni.h>
#include <android/log.h>
#include <stdlib.h>
#include <string.h>

//log定义
#define  LOG    "JNILOG" // 这个是自定义的LOG的TAG
#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,LOG,__VA_ARGS__) // 定义LOGD类型
#define  LOGI(...)  __android_log_print(ANDROID_LOG_INFO,LOG,__VA_ARGS__) // 定义LOGI类型
#define  LOGW(...)  __android_log_print(ANDROID_LOG_WARN,LOG,__VA_ARGS__) // 定义LOGW类型
#define LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,LOG,__VA_ARGS__) // 定义LOGE类型
#define LOGF(...)  __android_log_print(ANDROID_LOG_FATAL,LOG,__VA_ARGS__) // 定义LOGF类型

JNIEXPORT jstring JNICALL
Java_com_it_hellojni_MainActivity_sayHelloWorld(JNIEnv *env, jobject instance) {

    char *ptr = "hello world";
    return (*env)->NewStringUTF(env, ptr);
}


JNIEXPORT jint JNICALL
Java_com_it_hellojni_MainActivity_resultFromC(JNIEnv *env, jobject instance, jint a, jint b) {

    return a + b;
}

/**
 * 在c中方法要提前声明
 * @param str
 * @return
 */
char *handleStr(char *str) {
    char *header = str;
    char *tail = str;
    char temp;

    // 把tail指针移动到最后,注意是*tail不是tail
    while (*tail != '\0') {
        tail++;
    }

    tail--;

    // 首尾交换字符
    while (header < tail) {
        LOGE("sdfsf");
        temp = *header;
        *header = *tail;
        *tail = temp;
        header++;
        tail--;
    }

    return str;
}

JNIEXPORT jstring JNICALL
Java_com_it_hellojni_MainActivity_encodeString(JNIEnv *env, jobject instance, jstring str_) {
    // 在内存中申请一块地址,str是首地址
    char *pStr;
    const char *str = (*env)->GetStringUTFChars(env, str_, 0);
    pStr = handleStr(str);
    // 释放内存
    (*env)->ReleaseStringUTFChars(env, str_, str);

    return (*env)->NewStringUTF(env, pStr);
}


JNIEXPORT void JNICALL
Java_com_it_hellojni_MainActivity_sortArray(JNIEnv *env, jobject instance, jintArray arr_) {

    int i, j, temp;

    jint *arr = (*env)->GetIntArrayElements(env, arr_, NULL);
    jsize size = (*env)->GetArrayLength(env, arr_);

    for (i = 0; i < size - 1; i++) {
        for (j = i + 1; j < size; j++) {
            if (arr[i] > arr[j]) {
                temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }

    (*env)->ReleaseIntArrayElements(env, arr_, arr, 0);
}

JNIEXPORT void JNICALL
Java_com_it_hellojni_MainActivity_writeFile(JNIEnv *env, jobject instance, jstring filePath_,
                                            jstring fileContent_) {
    const char *filePath = (*env)->GetStringUTFChars(env, filePath_, 0);
    const char *fileData = (*env)->GetStringUTFChars(env, fileContent_, 0);

    FILE *file = fopen(filePath, "a+");
    if (file == NULL) {
        LOGI("file 不存在");
        return;
    }

    /**
     * 第一个参数是文件内容
     * 第二个参数是文件长度
     * 第三个参数是一次写入多少个字节
     * 第四个参数是要写入的文件
     */
    int size = fwrite(fileData, strlen(fileData), 1, file);
    if (size == 0) {
        LOGI("文件写入失败");
        return;
    }

    if(file != NULL){
        fclose(file);
    }
    LOGI("file 写入成功");
    (*env)->ReleaseStringUTFChars(env, filePath_, filePath);
}


