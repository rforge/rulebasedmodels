#include "defns.i"
#include "extern.i"
#include "rulebasedmodels.h"
#include "redefine.h"
#include "strbuf.h"

/* Don't want to include R.h, which has conflicts with cubist headers */
extern void Rprintf(const char *, ...);

/*
 * Reset all global variables to their initial value
 */
void initglobals(void)
/*   ---------- */
{
/*************************************************************************/
/*                                                                       */
/*              General data for Cubist                                  */
/*              -----------------------                                  */
/*                                                                       */
/* These variables are all defined in global.c.  Many aren't explicitly  */
/* initialized there, but are here, just in case.                        */
/*                                                                       */
/*************************************************************************/


    ClassAtt = 0;
    LabelAtt = 0;
    CWtAtt = 0;

    IgnoredVals = 0;
    IValsSize = 0;
    IValsOffset = 0;

    MaxAtt = 0;
    MaxDiscrVal = 3;
    Precision = 0;
    MaxLabel = 0;
    LineNo = 0;
    ErrMsgs = 0;
    AttExIn = 0;
    TSBase = 0;

    MaxCase = -1;

    Case = Nil;

    SaveCase = Nil;
    Blocked = Nil;
    SaveMaxCase = 0;

    MaxAttVal = Nil;
    Modal = Nil;

    SpecialStatus = Nil;

    AttDef = Nil;
    AttDefUses = Nil;

    AttName = Nil;
    AttValName = Nil;

    Of = 0;
    FileStem = "undefined";

    AttMean = Nil;
    AttSD = Nil;
    AttMaxVal = Nil;
    AttMinVal = Nil;
    AttPref = Nil;
    Ceiling = 0.0;
    Floor = 0.0;
    AvCWt = 0.0;

    ErrReduction = 1;

    AttUnit = Nil;

    AttPrec = Nil;

    Instance = Nil;
    Ref[0] = Nil;
    Ref[1] = Nil;
    MaxInstance = -1;
    KDTree = Nil;

    GNNEnv;  /* This is a struct, which I'm not going to initialize */
    RSPredVal = Nil;


/*************************************************************************/
/*                                                                       */
/*        Global data for Cubist used for building model trees           */
/*        ----------------------------------------------------           */
/*                                                                       */
/*************************************************************************/


    GEnv;  /* This is a struct, which I'm not going to initialize */

    TempMT = Nil;

    SRec = Nil;

    GlobalMean = 0.0;
    GlobalSD = 0.0;
    GlobalErr = 0.0;

    Fn[0] = '\0';

    Mf = 0;
    Pf = 0;


/*************************************************************************/
/*                                                                       */
/*      Global data for constructing and applying rules                  */
/*      -----------------------------------------------                  */
/*                                                                       */
/*************************************************************************/


    Rule = Nil;
    NRules = 0;
    RuleSpace = 0;

    Cttee = Nil;


/*************************************************************************/
/*                                                                       */
/*              Global parameters for Cubist                             */
/*              ----------------------------                             */
/*                                                                       */
/*************************************************************************/


    VERBOSITY = 0;
    FOLDS = 10;
    NN = 0;
    MEMBERS = 1;

    MAXD = 0.0;

    XVAL = 0;
    CHOOSEMODE = 0;
    USEINSTANCES = 0;
    UNBIASED = 0;

    SAMPLE = 0.0;
    KRInit = 0;
    LOCK = false;

    MINITEMS = 0;
    MAXRULES = 100;

    EXTRAP = 0.1;
}

/*
 * Set global variables in preparation for creating a model
 */
void setglobals(int unbiased, char *composite, int neighbors, int committees,
                double sample, int seed, int rules, double extrapolation)
{
    /* XXX What about setting FOLDS? */

    UNBIASED = unbiased != 0 ? true : false;

    if (strcmp(composite, "yes") == 0) {
        USEINSTANCES = true;
        CHOOSEMODE = false;
    } else if (strcmp(composite, "auto") == 0) {
        USEINSTANCES = true;
        CHOOSEMODE = true;
    } else {
        USEINSTANCES = neighbors > 0;
        CHOOSEMODE = false;
    }

    NN = neighbors;
    MEMBERS = committees;
    SAMPLE = sample;
    KRInit = seed;
    MAXRULES = rules;
    EXTRAP = extrapolation;
}

void setOf()
{
    // XXX Experimental
    Of = rbm_fopen("rulebasedmodels.stdout", "w");
}

char *closeOf()
{
    if (Of) {
        rbm_fclose(Of);
        return strbuf_getall((STRBUF *) Of);
    } else {
        return "";
    }
}
