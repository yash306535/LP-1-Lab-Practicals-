#include <jni.h>
#include "A3.h"

// --- Addition ---
JNIEXPORT jint JNICALL Java_A3_add(JNIEnv *env, jobject obj, jint a, jint b) {
    return a + b;
}

// --- Subtraction ---
JNIEXPORT jint JNICALL Java_A3_sub(JNIEnv *env, jobject obj, jint a, jint b) {
    return a - b;
}

// --- Multiplication ---
JNIEXPORT jint JNICALL Java_A3_mul(JNIEnv *env, jobject obj, jint a, jint b) {
    return a * b;
}

// --- Division ---
JNIEXPORT jint JNICALL Java_A3_div(JNIEnv *env, jobject obj, jint a, jint b) {
    if (b == 0) return 0; // avoid divide-by-zero
    return a / b;
}

//Command to run the c file = gcc -I"%JAVA_HOME%\include" -I"%JAVA_HOME%\include\win32" -shared -o A3.dll A3.c
