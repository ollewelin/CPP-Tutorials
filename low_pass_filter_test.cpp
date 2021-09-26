#include <QCoreApplication>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    float input = 1.0f;
    float output = 0.0f;

    float tau = 100.0f;
    float sampl_time = 0.5f;
    float filter_constant = sampl_time/tau;

    int test_nr_of_sample = 200;



    //Test step response test_nr_of_sample sample
    for(int i=0;i<test_nr_of_sample;i++){
        output = ((input - output) * filter_constant) + output;//low pass filter
        printf("Sample nr %d , output = %f\n", i, output);
    }

    printf("tau = %f\n", tau);
    printf("sampl_time = %f\n", sampl_time);
    printf("filter_const = %f\n", filter_constant);
    printf("The for loop of %d samples will in real world take %f seconds to run\n", test_nr_of_sample, (float)test_nr_of_sample * sampl_time);

    return a.exec();
}
