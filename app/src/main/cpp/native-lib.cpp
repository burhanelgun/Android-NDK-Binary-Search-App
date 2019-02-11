#include <jni.h>
#include <climits>

#define JNI_METHOD(RETURN_TYPE,METHOD_NAME)\
    extern "C" JNIEXPORT RETURN_TYPE JNICALL Java_com_example_native2_MainActivity_##METHOD_NAME


JNI_METHOD(jintArray ,largestSumContiguousSubArray)(JNIEnv *env, jobject instance, jintArray arr_) {

    jint *arr = env->GetIntArrayElements(arr_, NULL); //obtain a pointer to the elements of the array
    jsize len = env->GetArrayLength(arr_); //obtain the length of the array by calling the JNI function
    jint  i=0,max_so_far = INT_MIN, max_ending_here = 0,start =0, end = 0, s=0;


    //algorithm
    for (i=0; i< len; i++ )
    {
        max_ending_here += arr[i];

        if (max_so_far < max_ending_here)
        {
            max_so_far = max_ending_here;
            start = s;
            end = i;
        }

        if (max_ending_here < 0)
        {
            max_ending_here = 0;
            s = i + 1;
        }
    }

    //creating result array
    jintArray resultArr_ = env->NewIntArray(10);
    if (resultArr_ == NULL) {
        return NULL; /* out of memory error thrown */
    }



    env->SetIntArrayRegion(resultArr_, start, end+1, arr);//geeting subarray from arr to resultArr_
    env->ReleaseIntArrayElements(arr_, arr, 0); //enables the JNI to copy back and free the memory referenced by the body parameter if it is a copy of the original Java array
    return  resultArr_; //resturning result array

}
JNI_METHOD(jint ,BinarySearch)(JNIEnv *env, jobject instance, jintArray arr_,jint val) {

    jint *arr = env->GetIntArrayElements(arr_, NULL); //obtain a pointer to the elements of the array
    jsize len = env->GetArrayLength(arr_); //obtain the length of the array by calling the JNI function
    jint first=0;
    jint last=len-1;
    jint middle=0;

    while (first <= last)
    {
        middle = (first + last) / 2; //this finds the mid point
        if (arr[middle] == val) {
            return middle;
        }
        else if (arr[middle]> val) // if it's in the lower half
        {
            last = middle - 1;
        }
        else {
            first = middle + 1;                 //if it's in the upper half
        }
    }
    return -1;  // not found


}

JNI_METHOD(jint ,binarySearch)(JNIEnv *env, jobject instance, jintArray arr_,jint val) {

    jint *arr = env->GetIntArrayElements(arr_, NULL); //obtain a pointer to the elements of the array
    jsize len = env->GetArrayLength(arr_); //obtain the length of the array by calling the JNI function
    jint first=0;
    jint last=len-1;
    jint middle=0;

    while (first <= last)
    {
        middle = (first + last) / 2; //this finds the mid point
        if (arr[middle] == val) {
            return middle;
        }
        else if (arr[middle]> val) // if it's in the lower half
        {
            last = middle - 1;
        }
        else {
            first = middle + 1;                 //if it's in the upper half
        }
    }
    return -1;  // not found


}
extern "C"
JNIEXPORT jintArray JNICALL
Java_com_example_native2_MainActivity_insertionSort(JNIEnv *env, jobject instance, jintArray arr_) {
    jint *arr = env->GetIntArrayElements(arr_, NULL);
    jsize len = env->GetArrayLength(arr_); //obtain the length of the array by calling the JNI function


    int i, key, j;
    for (i = 1; i < len; i++)
    {
        key = arr[i];
        j = i-1;

        /* Move elements of arr[0..i-1], that are
           greater than key, to one position ahead
           of their current position */
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