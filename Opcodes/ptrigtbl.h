/*
    ptrigtbl.h:

    Copyright (C) 1997 Paris Smaragdis, John ffitch

    This file is part of Csound.

    The Csound Library is free software; you can redistribute it
    and/or modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) any later version.

    Csound is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with Csound; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA
    02111-1307 USA
*/

#define GOOD_TRIG

#if defined(GOOD_TRIG)
#define FHT_SWAP(a,b,t) {(t)=(a);(a)=(b);(b)=(t);}

#define TRIG_VARS                   \
    MYFLT   coswrk[24], sinwrk[24]; \
    long    t_lam = 0L;             \
    coswrk[0] = FL(0.0);            \
    sinwrk[0] = FL(1.0);

#define TRIG_INIT(k,c,s)            \
    {                               \
        long i;                     \
        for (i = 1; i <= k; i++) {  \
            coswrk[i] = costab[i];  \
            sinwrk[i] = sintab[i];  \
        }                           \
        t_lam = 0;                  \
        c = FL(1.0);                \
        s = FL(0.0);                \
    }

#define TRIG_NEXT(k,c,s)                        \
    {                                           \
        long i, j;                              \
        (t_lam)++;                              \
        for (i = 0; !((1L << i) & t_lam); i++); \
        i = k - i;                              \
        s = sinwrk[i];                          \
        c = coswrk[i];                          \
        if (i > 1) {                            \
            for (j = k - i + 2; (1L << j) & t_lam; j++);        \
            j = k - j;                          \
            sinwrk[i] = halsec[i] * (sinwrk[i-1] + sinwrk[j]);  \
            coswrk[i] = halsec[i] * (coswrk[i-1] + coswrk[j]);  \
        }                                       \
    }
#endif

#if defined(FAST_TRIG)
#define TRIG_VARS       MYFLT t_c,t_s;

#define TRIG_INIT(k,c,s)            \
    {                               \
        t_c = costab[k];            \
        t_s = sintab[k];            \
        c = 1;                      \
        s = 0;                      \
    }

#define TRIG_NEXT(k,c,s)            \
    {                               \
        MYFLT t = c;                \
        c   = t*t_c - s*t_s;        \
        s   = t*t_s + s*t_c;        \
    }
#endif

#define SQRT2_2         (FL(0.70710678118654752440084436210484))
#define SQRT2           (FL(2.0) * FL(0.70710678118654752440084436210484))

static const MYFLT halsec[20]=
    {
      FL(0.0),
      FL(0.0),
      FL(.54119610014619698439972320536638942006107206337801),
      FL(.50979557910415916894193980398784391368261849190893),
      FL(.50241928618815570551167011928012092247859337193963),
      FL(.50060299823519630134550410676638239611758632599591),
      FL(.50015063602065098821477101271097658495974913010340),
      FL(.50003765191554772296778139077905492847503165398345),
      FL(.50000941253588775676512870469186533538523133757983),
      FL(.50000235310628608051401267171204408939326297376426),
      FL(.50000058827484117879868526730916804925780637276181),
      FL(.50000014706860214875463798283871198206179118093251),
      FL(.50000003676714377807315864400643020315103490883972),
      FL(.50000000919178552207366560348853455333939112569380),
      FL(.50000000229794635411562887767906868558991922348920),
      FL(.50000000057448658687873302235147272458812263401372)
    };
static const MYFLT costab[20]=
    {
      FL(.00000000000000000000000000000000000000000000000000),
      FL(.70710678118654752440084436210484903928483593768847),
      FL(.92387953251128675612818318939678828682241662586364),
      FL(.98078528040323044912618223613423903697393373089333),
      FL(.99518472667219688624483695310947992157547486872985),
      FL(.99879545620517239271477160475910069444320361470461),
      FL(.99969881869620422011576564966617219685006108125772),
      FL(.99992470183914454092164649119638322435060646880221),
      FL(.99998117528260114265699043772856771617391725094433),
      FL(.99999529380957617151158012570011989955298763362218),
      FL(.99999882345170190992902571017152601904826792288976),
      FL(.99999970586288221916022821773876567711626389934930),
      FL(.99999992646571785114473148070738785694820115568892),
      FL(.99999998161642929380834691540290971450507605124278),
      FL(.99999999540410731289097193313960614895889430318945),
      FL(.99999999885102682756267330779455410840053741619428)
    };
static const MYFLT sintab[20]=
    {
      FL(1.0000000000000000000000000000000000000000000000000),
      FL(.70710678118654752440084436210484903928483593768846),
      FL(.38268343236508977172845998403039886676134456248561),
      FL(.19509032201612826784828486847702224092769161775195),
      FL(.09801714032956060199419556388864184586113667316749),
      FL(.04906767432741801425495497694268265831474536302574),
      FL(.02454122852291228803173452945928292506546611923944),
      FL(.01227153828571992607940826195100321214037231959176),
      FL(.00613588464915447535964023459037258091705788631738),
      FL(.00306795676296597627014536549091984251894461021344),
      FL(.00153398018628476561230369715026407907995486457522),
      FL(.00076699031874270452693856835794857664314091945205),
      FL(.00038349518757139558907246168118138126339502603495),
      FL(.00019174759731070330743990956198900093346887403385),
      FL(.00009587379909597734587051721097647635118706561284),
      FL(.00004793689960306688454900399049465887274686668768)
    };

