#include <stdio.h>
#include "sbml/SBMLTypes.h"

int main(void){
    SBMLDocument_t *d;
    Model_t *m;
    ListOf_t *los, *lor, *lop;
    Species_t *s1, *s2;
    Reaction_t *r;
    KineticLaw_t *kl;
    Parameter_t *p;
    double t, ds1dt, ds2dt;
    double amo_s1, amo_s2, k;
    double dt = 0.1;
    const char *name_s1, *name_s2, *formula;
    
    d = readSBML("simple.xml");
    m = SBMLDocument_getModel(d);

    //分子
    los = Model_getListOfSpecies(m);
    s1 = (Species_t*)ListOf_get(los, 0);
    name_s1= Species_getName(s1); //？？
    amo_s1 = Species_getInitialAmount(s1);

    s2 = (Species_t*)ListOf_get(los, 1);
    name_s2 = Species_getName(s2);
    amo_s2 = Species_getInitialAmount(s2);

    //ReactionとParameter
    lor = Model_getListOfReactions(m);
    r = (Reaction_t*)ListOf_get(lor, 0);
    kl = Reaction_getKineticLaw(r);
    formula = KineticLaw_getFormula(kl);
    lop = KineticLaw_getListOfParameters(kl);

    p = (Parameter_t*)ListOf_get(lop, 0);
    k = Parameter_getValue(p);

    printf("s1's name:%s (InitialAmount = %f)\n", name_s1, amo_s1);
    printf("s2's name:%s (InitialAmount = %f)\n", name_s2, amo_s2);
    printf("Reaction formula: v = %s\n\n", formula);

    printf("t, [%s], [%s]\n", name_s1, name_s2);

    double d1,d2,d3,d4;
    for(t = 0.0; t < 10.0; t = t + dt){
        printf("%f, %f, %f\n", t, amo_s1, amo_s2);

        ds1dt = -k * amo_s1;
        ds2dt = k * amo_s1; 
        
        d1 = ds1dt * dt;
        amo_s1 = amo_s1 + ds1dt * dt/2;
        d2 = k * amo_s1;
        amo_s1 = amo_s1 + ds1dt * dt/2;
        d3 = k * amo_s1;
        amo_s1 = amo_s1 + ds1dt * dt;
        d4 = k * amo_s1;

        d1 = ds1dt * dt;
        amo_s2 = amo_s2 + ds1dt * dt/2;
        d2 = k * amo_s2;
        amo_s2 = amo_s2 + ds1dt * dt/2;
        d3 = k * amo_s2;
        amo_s2 = amo_s2 + ds1dt * dt;
        d4 = k * amo_s2;

        amo_s1 += (d1 + 2*d2 + 2*d3 + d4)/6;
        amo_s2 += (d1 + 2*d2 + 2*d3 + d4)/6;
    }

    SBMLDocument_free(d);
    return 0;
}
