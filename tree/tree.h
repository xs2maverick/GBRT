#ifndef TREE_H
#define TREE_H

#include <opencv2/opencv.hpp>
#include "basetree.h"
#include "util.h"

using cv::Mat;
using cv::Mat_;

class Criterion;
class Splitter;

class BaseDecisionTree
{
public:
    /**
     * @brief Base class for decision trees.
     * @param criterion
     * @param splitter
     * @param max_depth
     * @param min_samples_split
     * @param min_samples_leaf
     * @param min_weight_fraction_leaf
     * @param max_features
     * @param max_leaf_nodes
     * @param random_state
     * @param class_weight
     * @param is_classification 0 for classification, 1 for regression
     */
    BaseDecisionTree(Criterion& criterion,
                     Splitter& splitter,
                     int max_depth,
                     int min_samples_split,
                     int min_samples_leaf,
                     double min_weight_fraction_leaf,
                     int max_features,
                     int max_leaf_nodes,
                     int random_state,
                     Mat_<double> class_weight,
                     int is_classification);
    ~BaseDecisionTree();

    /**
     * @brief Build a decision tree for the training set (X, y).
     * @param _X The training input samples, shape = [n_sampels, n_features]
     * @param _y The target values, shape = [n_samples]
     * @param sample_weight Sample weights. If total size equals to zero, then samples are equally weighted.
     * @return error_code
     */
    int fit(Mat_<double> _X,
             Mat_<double> _y,
             Mat_<double> sample_weight);

    /**
     * @brief Predict class or regression value of X.
     * For a classification modle, the predicted class for each sample in X is returned.
     * For a regression model, the predicted value based on X is returned.
     * @param _X The input samples, shape = [n_samples]
     * @return The predicted classes, or the predict values
     */
    Mat_<double> predict(Mat_<double> _X);

   /**
    * @brief Return the feature importances.
    * The importance of a feature is computed as the normalized total
    * reduction of the criterion brought by the feature
    * @return Mat, shape = [n_features]
    */
    Mat_<double> feature_importances();

public:
    Criterion& _criterion;
    Splitter& _splitter;
    int _max_depth;
    int _min_samples_split;
    int _min_samples_leaf;
    double _min_weight_fraction_leaf;
    int _max_features;
    int _random_state;
    int _max_leaf_nodes;
    Mat_<double> _class_weight;

    int _n_samples;
    int _n_features;
    int _is_classification;

    Tree _tree;
    int _max_features;
};

class DecisionTreeClassifier : public BaseDecisionTree
{
public:
    /**
     * @brief A decision tree classifier.
     * @param criterion
     * @param splitter
     * @param max_depth
     * @param min_samples_split
     * @param min_samples_leaf
     * @param min_weight_fraction_leaf
     * @param max_features
     * @param max_leaf_nodes
     * @param random_state
     * @param class_weight
     */
    DecisionTreeClassifier(Criterion& criterion,
                           Splitter& splitter,
                           int max_depth,
                           int min_samples_split,
                           int min_samples_leaf,
                           double min_weight_fraction_leaf,
                           int max_features,
                           int max_leaf_nodes,
                           int random_state,
                           Mat_<double> class_weight);
    virtual ~DecisionTreeClassifier();

    /**
     * @brief Predict class probabilities of the input samples X.
     * The predicted class probalility is the fraction of samples of the same class in a leaf.
     * @param _X The input samples, shape = [n_samples]
     * @return
     */
    Mat_<double> predict_proba(Mat_<double> _X);

    /**
     * @brief Predict class log-probabilities of the input samples X.
     * @param _X The input samples, shape = [n_samples]
     * @return
     */
    Mat_<double> predict_log_proba(Mat_<double> _X);
};

class DecisionTreeRegressor : public BaseDecisionTree
{
public:
    /**
     * @brief A decision tree regressor.
     * @param criterion
     * @param splitter
     * @param max_depth
     * @param min_samples_split
     * @param min_samples_leaf
     * @param min_weight_fraction_leaf
     * @param max_features
     * @param max_leaf_nodes
     * @param random_state
     * @param class_weight
     */
    DecisionTreeRegressor(Criterion& criterion,
                          Splitter& splitter,
                          int max_depth,
                          int min_samples_split,
                          int min_samples_leaf,
                          double min_weight_fraction_leaf,
                          int max_features,
                          int max_leaf_nodes,
                          int random_state,
                          Mat_<double> class_weight);
    virtual ~DecisionTreeRegressor();
};

#endif // TREE_H
