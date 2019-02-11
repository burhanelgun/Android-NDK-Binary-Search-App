#include <jni.h>
#include <climits>

#define JNI_METHOD(RETURN_TYPE,METHOD_NAME)\
    extern "C" JNIEXPORT RETURN_TYPE JNICALL Java_com_example_native2_MainActivity_##METHOD_NAME


JNI_METHOD(jint ,binarySearch)(JNIEnv *env, jobject instance, jintArray arr_,jint val) {

    jint *arr = env->GetIntArrayElements(arr_, NULL); //obtain a pointer to the elements of the array
    jsize len = env->GetArrayLength(arr_); //obtain the length of the array by calling the JNI function
    jint first=0;
    jint last=len-1;
    jint middle=0;

    while (first <= last)
    {
        middle = (first + last) / 2;
        if (arr[middle] == val) {
            return middle;
        }
        else if (arr[middle]> val)
        {
            last = middle - 1;
        }
        else {
            first = middle + 1;
        }
    }
    return -1;


}

JNI_METHOD(jintArray ,insertionSort)(JNIEnv *env, jobject instance, jintArray arr_) {
    jint *arr = env->GetIntArrayElements(arr_, NULL);
    jsize len = env->GetArrayLength(arr_); //obtain the length of the array by calling the JNI function


    int i, key, j;
    for (i = 1; i < len; i++)
    {
        key = arr[i];
        j = i-1;

        while (j >= 0 && arr[j] > key)
        {
            arr[j+1] = arr[j];
            j = j-1;
        }
        arr[j+1] = key;
    }

    env->ReleaseIntArrayElements(arr_, arr, 0);

    return arr_;
}