#include "../../../../vowpalwabbit/parser.h"
#include "../../../../vowpalwabbit/vw.h"
#include "vw_errors.h"
#include "vw_learner_VWFloatLearner.h"

JNIEXPORT jfloat JNICALL Java_vw_learner_VWFloatLearner_predict(JNIEnv *env, jobject obj, jstring example_string, jboolean learn, jlong vwPtr) {
    float prediction = 0.0f;
    try {
        vw* vwInstance = (vw*)vwPtr;
        const char *utf_string = env->GetStringUTFChars(example_string, NULL);
        example *vec = VW::read_example(*vwInstance, utf_string);

        if (learn)
            vwInstance->l->learn(*vec);
        else
            vwInstance->l->predict(*vec);

        prediction = vec->pred.scalar;

        VW::finish_example(*vwInstance, vec);
        env->ReleaseStringUTFChars(example_string, utf_string);
        env->DeleteLocalRef(example_string);
    }
    catch (...) {
        rethrow_cpp_exception_as_java_exception(env);
    }
    return prediction;
}
