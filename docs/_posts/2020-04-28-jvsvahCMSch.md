---
layout: post
title:  "Rychlostní model JV svah ČM metodou tomografie povrchových vln "
date:   2020-04-28 20:00:00 +0200
categories: []
---


Pro účely testování lokačních algoritmů bylo zvoleno čtvercové území 100 km x 100 km,
do kterého z větší části zasahuje oblast jihovýchodních svahů Českého masívu.

V tomto území porovnáme účinek několika typů rychlostním modelů. 
Jedním z nich je rychlostni model vytvořený podle článku \[[Shippkus et al., 2018](#schippkus2018)\]
a podle dat publikovaných jako příloha k uvedenému článku
pod licencí [Creative Commons Attribution License](http://creativecommons.org/licenses/by/4.0/)

Nedomnívám se, že by tento rychlostní model byl vhodný pro účel lokace zemětřesení.
Lokace zemětřesení vyžaduje rychlostní model spíše generalizovaný, který nezavádí
do modelu anomálie bez dobrého podkladu a účelu.
Zde se nám ale laterálně nehomegenní  model hodí pro otestování programů NLL, které jsou schopné
pracovat i v podmínkách kontrastních rychlostních rozdílů a dokonce rychlostní inverze.

Problémem je převod rychlostí odvozený z povrchových vln na rychosti objemových příčných a podélných vln,
kterého se zde dopuštím. Tento převod je uskutečněný za předpokladu přímé úměry, který nemusí platit.

Schippkusův model byl vypočítán metodou seismické tomografie povrchových vln o poriodách 5s až 25s
jejichž zdrojem je mikroseismický šum a časy šíření šíření mezi stanicemi byly získány
výpočtem vzájemné korelace seismického signálu.

Pro výpočet byl použitý rastr s krokem 5 km x 5 km x 1 km do hloubky 30 km. Podmínkou pro tomografický
výpočet je dostatečný počet paprsků zasahujících výpočetní pixel. Tato podmínka není splněna na okrajích
a místy uvnitř řešené oblasti. V těchto místech, kde nebylo možné výpočet korektně provést, není
v publikovaných datech uvedená hodnota rychlosti, v pravidelném rastru hodnot jsou "díry".

![obr 1]({{site.baseurl}}/img/jvsvahCMsch_img1.png){: style="border: solid 1px"}   
Model \[[Shippkus et al., 2018](#schippkus2018)\]. Hloubka 10 km.

Model je produktem studie zaměřené na oblast Vídeňské pánve. Se vzdáleností od centrální časti modelu
se vzhledem k poloze použitých seismických stanic zhoršují podmínky pro korektní fungování tomografické metody.
Přesto vymezená oblast jihovýchodních svahů Českého masívu spadá do vnitřní části modelu, kde se ještě
můžeme pokusit publikovaný model použít.

## Technické úpravy modelu

Model byl přizpůsoben tak, aby mohl být použit pro výpočet časových polí pomocí metody sítí
(program Grid2Time ze sady NLL). Úpravy spočívají v omezení výřezu na zájmové území a převzorkování
s jemnějším krokem 0.5 km do izometrického gridu.
Postupně byly provedeny následující úpravy:

### Doplnění chybějících hodnot

První výpočetní operací na modelu bylo doplnění chybějících hodnot,
především v případě děr uvnitř rastru, a oříznutí okrajů.
Interpolace byla provedena v původním rastru 5 km x 5 km postupně po vrstvách.
Pro doplnění hodnot byla použitá iterační metoda založená na Poissonově rovnici, která zaplňuje
mezery v rastru konzervativním způsobem bez vzniku nových anomálií.

![obr 2]({{site.baseurl}}/img/jvsvahCMsch_img2.png){: style="border: solid 1px"}
Model interpolovaný a oříznutý. S vyznačeným zájmovým územím. Hloubka 10 km.

### Vymezení zájmového území, interpolace do gridu NLL a transformace veličin

Gridem NLL myslíme 3D síť ve formátu NonLinLoc.
Viz [Vše se točí kolem gridu]({{site.baseurl}}/2020/04/26/Grid.html){: target="_blank"}.
<!-- Viz [Vše se točí kolem gridu]({{site.baseurl}}{% link _posts/2020-04-26-Grid.md %}){: target="_blank"}. -->
Model je označený jako `jvsvahCMsch`, parametry jeho prostorového určení jsou zapsány
v souboru headeru `jvsvahCMsch.P.hdr`
```
201 201 80  -650.250000 -1230.250000 -0.750000  0.500000 0.500000 0.500000 SLOW_LEN
```
Požadovaná výsledná izometrická 3D síť má krok vzorkování 0.5 km, vzorkovaná veličina  
(parametr SLOW_LEN) je pomalost podélných vln násobená rozměrem buňky a
týká se zájmového území definovaného čtvercem 100 km x 100 km Křovákových souřadnicích.

Zatímco rastr původního modelu je vzorkovaný v kroku 5 km x 5 km x 1 km, obsahuje
hodnoty rychlosti odvozené z povrchových vln a je publikovaný v geografických souřadnicích.

Přeformátování dat tedy zahrnuje transformaci souřadnic, trojrozměrnou lineární interpolaci
a převod veličin. Pro převod veličin byl použitý nepříliš podložený předpoklad, že
rychlost odvozená z povrchových vln odpovídá rychlosti objemových příčných vln
a že poměr vP/vS = 1.70.

### Doplnění modelu

Model podle Schippkuse sahá od hloubky 1 km do hloubky 30 km.
Model jvsvahCMsch byl doplněn o vrstvu pláště v hloubce 35 km a rychlosti podélných vln 8.0 km/s.
Pro spodní kůru nad pláštěm byla použita konstantní rychlost 6.7 km/s.
Pro pokryv byla použita rychlost 4.0 km/s.





 



## Literatura

1. <a id="schippkus2018"></a>Schippkus, S., Zigone, D., Bokelmann, G., the AlpArray Working Group, Ambient-noise tomography of the wider Vienna Basin region, Geophysical Journal International, ggy259, [(https://doi.org/10.1093/gji/ggy259)](https://doi.org/10.1093/gji/ggy259), 2018


