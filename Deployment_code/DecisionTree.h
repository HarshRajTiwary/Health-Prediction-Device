#pragma once
// #include <cstdarg>
namespace Eloquent {
    namespace ML {
        namespace Port {
            class DecisionTree {
                public:
                    /**
                    * Predict class for features vector
                    */
                    int predict(float *x) {
                        if (x[2] <= 95.5) {
                            if (x[2] <= 94.0) {
                                return 1;
                            }

                            else {
                                if (x[0] <= 96.5) {
                                    return 1;
                                }

                                else {
                                    if (x[0] <= 99.0) {
                                        return 0;
                                    }

                                    else {
                                        return 1;
                                    }
                                }
                            }
                        }

                        else {
                            if (x[1] <= 37.25) {
                                if (x[0] <= 61.0) {
                                    return 1;
                                }

                                else {
                                    return 0;
                                }
                            }

                            else {
                                return 1;
                            }
                        }
                    }

                protected:
                };
            }
        }
    }