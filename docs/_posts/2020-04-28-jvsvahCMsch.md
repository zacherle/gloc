---
layout: post
title:  "Rychlostní model JV svah ČM metodou tomografie povrchových vln "
date:   2020-04-28 20:00:00 +0200
categories: []
---


Pro účely testování lokačních algoritmů bylo zvoleno čtvercové území 100 km x 100 km,
do kterého z&nbsp;větší části zasahuje oblast jihovýchodních svahů Českého masívu.

V&nbsp;tomto území porovnáme účinek několika typů rychlostním modelů. 
Jedním z&nbsp;nich je rychlostni model vytvořený podle článku \[[Shippkus et al., 2018](#schippkus2018)\]
a podle dat publikovaných jako příloha k&nbsp;uvedenému článku
pod licencí [Creative Commons Attribution License](http://creativecommons.org/licenses/by/4.0/)

Nedomnívám se, že by tento rychlostní model byl vhodný pro účel lokace zemětřesení.
Lokace zemětřesení vyžaduje rychlostní model spíše generalizovaný, který nezavádí
do modelu anomálie bez dobrého podkladu a účelu.
Zde se nám ale laterálně nehomogenní  model hodí pro otestování programů NLL, které jsou schopné
pracovat i v&nbsp;podmínkách kontrastních rychlostních rozdílů a dokonce rychlostní inverze.

Problémem je převod rychlostí odvozených z&nbsp;povrchových vln na rychlosti objemových příčných a podélných vln,
kterého se zde dopouštím. Tento převod je uskutečněný za předpokladu přímé úměry, který nemusí platit.

## Data

Schippkusův rychlostní model byl vypočítán metodou seismické tomografie povrchových vln
o&nbsp;periodách 5s až 25s jejichž zdrojem je mikroseismický šum a časy šíření šíření mezi stanicemi
byly získány výpočtem vzájemné korelace seismického signálu.

Pro výpočet byl použitý rastr s&nbsp;krokem 5 km x 5 km x 1 km do hloubky 30 km. Podmínkou pro tomografický
výpočet je dostatečný počet paprsků zasahujících výpočetní pixel. Tato podmínka není splněna na okrajích
a místy uvnitř řešené oblasti. V&nbsp;těchto místech, kde nebylo možné výpočet korektně provést, není
v&nbsp;publikovaných datech uvedená hodnota rychlosti, v&nbsp;pravidelném rastru hodnot jsou "díry".

![obr 1]({{site.baseurl}}/img/jvsvahCMsch_img1.png){: style="border: solid 1px"}   
Obr 1: Model \[[Shippkus et al., 2018](#schippkus2018)\]. Hloubka 10 km.

Model je produktem studie zaměřené na oblast Vídeňské pánve. Se vzdáleností od centrální části modelu
se vzhledem k&nbsp;poloze použitých seismických stanic zhoršují podmínky pro korektní fungování tomografické metody.
Přesto vymezená oblast jihovýchodních svahů Českého masívu spadá do vnitřní části modelu, kde se ještě
můžeme pokusit publikovaný model použít.

## Technické úpravy modelu

Název modelu je "jvsvahCMsch".   
Model byl přizpůsoben tak, aby mohl být použit pro výpočet časových polí pomocí metody sítí
(program Grid2Time ze sady NLL). Úpravy spočívají v&nbsp;omezení výřezu na zájmové území a převzorkování
s&nbsp;jemnějším krokem 0.5 km do izometrického gridu.
Postupně byly provedeny následující úpravy:

### Doplnění chybějících hodnot

První výpočetní operací na modelu bylo doplnění chybějících hodnot,
především v&nbsp;případě děr uvnitř rastru, a oříznutí okrajů.
Interpolace byla provedena v&nbsp;původním rastru 5 km x 5 km postupně po vrstvách.
Pro doplnění hodnot byla použitá iterační metoda založená na Poissonově rovnici, která zaplňuje
mezery v&nbsp;rastru konzervativním způsobem bez vzniku nových anomálií.

![obr 2]({{site.baseurl}}/img/jvsvahCMsch_img2.png){: style="border: solid 1px"}
Obr 2: Model doplněný a oříznutý. S&nbsp;vyznačeným zájmovým územím. Hloubka 10 km.

### Vymezení zájmového území a interpolace do gridu NLL a transformace veličin

Gridem NLL myslíme 3D síť ve formátu NonLinLoc.
Viz [Vše se točí kolem gridu]({{site.baseurl}}/2020/04/26/Grid.html){: target="_blank"}.
Požadovaná výsledná izometrická 3D síť má krok vzorkování 0.5 km a
týká se zájmového území definovaného čtvercem 100 km x 100 km v&nbsp;Křovákových souřadnicích.
Zatímco rastr původního modelu je vzorkovaný v&nbsp;kroku 5 km x 5 km x 1 km a
je publikovaný v&nbsp;geografických souřadnicích.
Přeformátování dat tedy zahrnuje transformaci souřadnic a trojrozměrnou lineární interpolaci.

![obr 3]({{site.baseurl}}/img/jvsvahCMsch6_img3.png)
Obr 3: Převzorkovaný model jvsvahCMsch v&nbsp;několika hloubkových úrovních.


### Transformace veličin

Pro přepočet rychlostního modelu na pole časů šíření seismických vln potřebuje program Grid2Time
rychlostní model ovzorkovaný v&nbsp;izometrickém gridu, ve kterém vzorkovaná veličina
(parametr SLOW\_LEN) je pomalost podélných vln násobená rozměrem buňky.
To odpovídá nejkratšímu času, za který může seismický signál projít danou buňkou.
Zatímco rastr původního modelu obsahuje hodnoty rychlosti odvozené z&nbsp;povrchových vln.

Pro převod veličin byl použitý nepříliš podložený předpoklad, že
rychlost odvozená z&nbsp;povrchových vln odpovídá rychlosti objemových příčných vln
a že poměr vP/vS = 1.70.

![obr 4]({{site.baseurl}}/img/jvsvahCMsch_img4.png)
Obr 4: Data typu SLOW\_LEN uložená v&nbsp;gridu jvsvahCMsch. Hloubka 10 km.

### Doplnění vrstev modelu

Model podle Schippkuse sahá od hloubky 1 km do hloubky 30 km.
Model jvsvahCMsch byl doplněn o&nbsp;vrstvu pláště v&nbsp;hloubce 35 km o&nbsp;rychlosti podélných vln 8.0 km/s.
Pro spodní kůru nad pláštěm byla použita konstantní rychlost 6.7 km/s.
Pro pokryv byla použita rychlost 4.0 km/s.


![obr 5]({{site.baseurl}}/img/jvsvahCMsch_img5.png)
Obr 5: Řez modelem jvsvahCMsch v&nbsp;profilu AA' (bez doplněných vrstev).
Rychlost v_P přepočítaná z&nbsp;rychlosti povrchových vln.

## Model jvsvahCMsch

Výsledný grid formátu NLL se skládá ze dvou souborů:
- `jvsvahCMsch.P.mod.buf` -- binárně zapsané pravidelně ovzorkované hodnoty pole modelu
- `jvsvahCMsch.P.mod.hdr` -- záhlaví, které popisuje prostorové určení a typ dat

Parametry prostorového určení modelu a typu dat v&nbsp;souboru headeru `jvsvahCMsch.P.mod.hdr`
```
201 201 80  -650.250000 -1230.250000 -0.750000  0.500000 0.500000 0.500000 SLOW_LEN FLOAT
```

Na území modelu se nachází několik seismických stanic. Jen pro tyto stanice lze vypočítat
pole časů šíření seismických vln a použít je pro lokaci zemětřesení.

Všechna data modelu jsou přístupná ve sdílené složce `\data\models\NLL`, včetně souřadnic
stanic `jvsvahCMsch.P.mod.stations` a předpočítaných časů.

## Komentář k&nbsp;modelu

Na řezu modelem je vidět rychlostní inverze v&nbsp;krystaliniku v&nbsp;západní a severozápadní části modelu.
Charakter modelu se mění v&nbsp;blízkosti stanice KRUC, od které se také směrem na západ a severozápad zhoršuje
hustota měřených dat použitých pro výpočet modelu. Proto se domnívám, že se jedná spíš o&nbsp;efekt postupu
použitého při tvorbě modelu.
To by stálo za podrobnější rozbor a diskusi.



## Literatura

1. <a id="schippkus2018"></a>Schippkus, S., Zigone, D., Bokelmann, G., the AlpArray Working Group, Ambient-noise tomography of the wider Vienna Basin region, Geophysical Journal International, ggy259, [(https://doi.org/10.1093/gji/ggy259)](https://doi.org/10.1093/gji/ggy259), 2018


