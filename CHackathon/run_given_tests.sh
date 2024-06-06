g++ giventests/laneDepartureGivenTests.cpp -o laneDepartureGivenTests -lgtest -lgtest_main -pthread -std=c++11
./laneDepartureGivenTests

g++ giventests/tyrePressureMonitorGivenTests.cpp -o tyrePressureMonitorGivenTests -lgtest -lgtest_main -pthread -std=c++11
./tyrePressureMonitorGivenTests

g++ giventests/blindSpotDetectionGivenTests.cpp -o blindSpotDetectionGivenTests -lgtest -lgtest_main -pthread -std=c++11
./blindSpotDetectionGivenTests

g++ giventests/airbagActuatorGivenTests.cpp -o airbagActuatorGivenTests -lgtest -lgtest_main -pthread -std=c++11
./airbagActuatorGivenTests

g++ giventests/reverseCameraCategorizationGivenTests.cpp -o reverseCameraCategorizationGivenTests -lgtest -lgtest_main -pthread -std=c++11
./reverseCameraCategorizationGivenTests

g++ giventests/drivingRangeEstimatorGivenTests.cpp -o drivingRangeEstimatorGivenTests -lgtest -lgtest_main -pthread -std=c++11
./drivingRangeEstimatorGivenTests

rm ./laneDepartureGivenTests ./tyrePressureMonitorGivenTests ./blindSpotDetectionGivenTests ./airbagActuatorGivenTests ./reverseCameraCategorizationGivenTests ./drivingRangeEstimatorGivenTests