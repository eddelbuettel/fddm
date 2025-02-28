// Header file to declare constants and functions
// This file must have a .h extension rather than .hpp extension because then
// R CMD Check will fail

#include <Rcpp.h>
// [[Rcpp::plugins(cpp11)]]
#include <cmath>

using std::vector;
using std::string;
using std::log;
using std::exp;
using std::sqrt;
using std::min;
using std::max;
using std::ceil;
using std::isfinite;
using std::isnan;
using std::isnormal;
using Rcpp::stop;
using Rcpp::NumericVector;



// Constants

static const double SV_THRESH = 0; // threshold for using variable drift rate
static const double LOG_100 = log(100);
static const double PI_CONST = 3.14159265358979323846; // define pi like C++
static const double LOG_PI = log(PI_CONST);
static const double LOG_2PI_2 = 0.5 * log(2 * PI_CONST);
static const double SQRT_2PI = sqrt(2 * PI_CONST);
static const char EMPTYCHAR = '\0'; // literally, the empty character
// INT_MAX is in num_funcs.cpp, maximum value of the int data type = 2147483647



// define types for functions in if-else in cpp_dfddm.cpp
typedef int    (*NumFunc)(const double&, const double&, const double&);
typedef double (*SumFunc)(const double&, const double&, const double&,
                          const int&, const double&);
typedef double (*DenFunc)(const double&, const double&, const double&,
                          const double&, const double&, const double&,
                          const int&, const NumFunc&, const SumFunc&);



// Number of Terms

int ks_Gon(const double& t, const double& w, const double& err);
int ks_Nav(const double& t, const double& w, const double& err);
int kl_Nav(const double& t, const double& w, const double& err);



// Infinite Summation Approximations

double small_sum_eps_17(const double& t, const double& a, const double& w,
                        const int& ks, const double& err);
double small_sum_eps_14(const double& t, const double& a, const double& w,
                        const int& ks, const double&  err);
double small_sum_2017(const double& t, const double& a, const double& w,
                      const int& ks, const double& err);
double small_sum_2014(const double& t, const double& a, const double& w,
                      const int& ks, const double& err);
double large_sum_Nav(const double& t, const double& a, const double& w,
                     const int& kl, const double& err);



// Density Functions
double ff(const double& t, const double& a, const double& v,
          const double& w, const double& sv, const double& err,
          const int& max_terms_large, const NumFunc& numf, const SumFunc& sumf);
double ff_log(const double& t, const double& a, const double& v,
              const double& w, const double& sv, const double& err,
              const int& max_terms_large,
              const NumFunc& numf, const SumFunc& sumf);
double fs(const double& t, const double& a, const double& v,
          const double& w, const double& sv, const double& err,
          const int& max_terms_large, const NumFunc& numf, const SumFunc& sumf);
double fs_log(const double& t, const double& a, const double& v,
              const double& w, const double& sv, const double& err,
              const int& max_terms_large,
              const NumFunc& numf, const SumFunc& sumf);
double fl(const double& t, const double& a, const double& v,
          const double& w, const double& sv, const double& err,
          const int& max_terms_large, const NumFunc& numf, const SumFunc& sumf);
double fl_log(const double& t, const double& a, const double& v,
              const double& w, const double& sv, const double& err,
              const int& max_terms_large,
              const NumFunc& numf, const SumFunc& sumf);
double fc(const double& t, const double& a, const double& v,
          const double& w, const double& sv, const double& err,
          const int& max_terms_large, const NumFunc& numf, const SumFunc& sumf);
double fc_log(const double& t, const double& a, const double& v,
              const double& w, const double& sv, const double& err,
              const int& max_terms_large,
              const NumFunc& numf, const SumFunc& sumf);
double fb(const double& t, const double& a, const double& v,
          const double& w, const double& sv, const double& err,
          const int& max_terms_large, const NumFunc& numf, const SumFunc& sumf);
double fb_log(const double& t, const double& a, const double& v,
              const double& w, const double& sv, const double& err,
              const int& max_terms_large,
              const NumFunc& numf, const SumFunc& sumf);



// Helper Functions
void determine_method(const std::string& n_terms_small,
                      const std::string& summation_small,
                      const std::string& scale,
                      NumFunc& numf, SumFunc& sumf, DenFunc& denf,
                      double& rt0, const bool& log_prob);
void convert_responses(const SEXP& response, int& Nres, int& Nmax,
                       vector<double>& out, const double& rt0, bool& valid);
bool parameter_check(const int& Nrt, int& Nres, const int& Na, const int& Nv,
                     const int& Nt0, const int& Nw, const int& Nsv,
                     const int& Nsig, const int& Nerr, int& Nmax,
                     const NumericVector& rt, const SEXP& response,
                     const NumericVector& a, const NumericVector& v,
                     const NumericVector& t0, const NumericVector& w,
                     const NumericVector& sv, const NumericVector& sigma,
                     const NumericVector& err,
                     vector<double>& out, const double& rt0);
void calculate_pdf(const int& Nrt, const int& Na, const int& Nv, const int& Nt0,
                   const int& Nw, const int& Nsv, const int& Nsig,
                   const int& Nerr, const int& Nmax,
                   const NumericVector& rt,
                   const NumericVector& a, const NumericVector& v,
                   const NumericVector& t0, const NumericVector& w,
                   const NumericVector& sv, const NumericVector& sigma,
                   const NumericVector& err, vector<double>& out,
                   const int& max_terms_large,
                   const NumFunc& numf, const SumFunc& sumf,
                   const DenFunc& denf, const double& rt0);
