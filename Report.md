# Tagok

| Név                     | Github azonosító | Javasolt relatív érdemjegy | Becsült óra | Indoklás                                                                                                                                      |
| ----------------------- | ---------------- | -------------------------- | ----------- | --------------------------------------------------------------------------------------------------------------------------------------------- |
| Balogh Máté             | @Cerberuuus      | 0                          | ~25         | Rendesen elkészített, körültekintően feltöltött megoldások, de egyben kevesebb feladat elvállalása. Alapos review végzése.                    |
| Baranyai Bence Bendegúz | @bencebaranyai   | +1                         | ~40         | Minőségi, részletes munka, gyors reagálás a kiírt feladatokra, gondos részletre figyelés, akár komplexebb feladatoknál is.                    |
| Karcag Tamás            | @karcagtamas     | +1                         | ~50         | Kiosztott feladatok határidőn belüli, kidolgozott formában való leadása. Körültekintő review végzés a saját és a pár csapat számára egyaránt. |

# Videók

- [Gameplay](/videos/gameplay.mp4)
- [CodeBaseDefense](/videos/codebasedefense.mp4)

# Befejezett feladatok

| Feladat      | Merge ideje a határidóhöz (nap) | Change request körök | Reviewer                                                                  | (Fő)fejlesztő                |
| ------------ | ------------------------------- | -------------------- | ------------------------------------------------------------------------- | ---------------------------- |
| Feladat 1    | -2                              | 2                    | @oliverosz                                                                | @pluplusplus team            |
| Feladat 2    | -1                              | 2                    | @oliverosz                                                                | @pluplusplus team            |
| jsonparser   | 8 (késői review)                | 1                    | @wayzy                                                                    | @bencebaranyai               |
| levelup      | 0                               | 2                    | @oliverosz                                                                | @Cerberuuus                  |
| attackspeed  | -5                              | 1                    | @vizvezetek                                                               | @karcagtamas                 |
| documetation | -3                              | 1                    | @runtime_terror/@tamastomordi                                             | @karcagtamas, @bencebaranyai |
| unittests    | -1                              | 0                    | @runtime_terror/@tamastomordi, @karcagtamas                               | @bencebaranyai               |
| makefile     | -2                              | 1                    | @hegyhati                                                                 | @Cerberuuus                  |
| refactor     | -1                              | 0                    | @hegyhati                                                                 | @karcagtamas                 |
| docker       | -3                              | 0                    | @hegyhati                                                                 | @karcagtamas                 |
| jsonpimp     | Merge: 11.17                    | 0                    | @karcagtamas, @Cerberuuus, @runtime_terror/@Jabezare                      | @bencebaranyai               |
| map          | Merge: 12.02                    | 2                    | @karcagtamas, @runtime_terror/@tamastomordi, @runtime_terror/@Jabezare    | @Cerberuuus                  |
| game         | Merge: 12.02                    | 2                    | @karcagtamas, @runtime_terror/@tamastomordi, @runtime_terror/@Jabezare    | @Cerberuuus                  |
| defense      | Merge: 11.24                    | 0                    | @runtime_terror/@tamastomordi, @bencebaranyai, @runtime_terror/@csibe1999 | @karcagtamas                 |
| damage       | Merge: 11.29                    | 1                    | @runtime_terror/@tamastomordi, @bencebaranyai                             | @karcagtamas                 |
| markedmap    | Merge: 12.03                    | 0                    | @karcagtamas, @runtime_terror/@tamastomordi, @Cerberuuus                  | @bencebaranyai               |
| preparedgame | Merge: 12.03                    | 0                    | @karcagtamas, @runtime_terror/@tamastomordi, @Cerberuuus                  | @bencebaranyai               |
| light radius | Merge: 12.04                    | 1                    | @bencebaranyai, @runtime_terror/@tamastomordi, @runtime_terror/@Jabezare  | @karcagtamas                 |
| rendering    | Merge: 12.08                    | 2                    | @karcagtamas, @Cerberuuus, @runtume_terror/@Jabezare                      | @bencebaranyai               |

# Unit tesztek

| Osztály                    | Publikus metódusok | Unit tesztelt metódusok sáma         | Unit tesztek száma |
| -------------------------- | ------------------ | ------------------------------------ | ------------------ |
| `JSON`                     | 6                  | 4                                    | 9                  |
| `Game`                     | 16                 | 10                                   | 4                  |
| `Unit`                     | 21                 | 15                                   | 5                  |
| `Map`                      | 8                  | 7                                    | 7                  |
| `Hero`                     | 2                  | 2                                    | 2                  |
| `Monster`                  | 2                  | 2                                    | 2                  |
| `Renderer (absztrakt)`     | -                  | 1                                    | 5                  |
| `PreparedGame`             | 2                  | Game osztállyal egyben tesztelve     |
| `MarkedMap`                | 10                 | Map osztállyal egyben tesztelve      |
| `Location`                 | 0                  |                                      |
| `Corner`                   | 1                  | Renderer osztállyal egyben tesztelve |
| `HeroSVGRenderer`          | 1                  | Renderer osztállyal egyben tesztelve |
| `HeroTextRenderer`         | 1                  | Renderer osztállyal egyben tesztelve |
| `ObserverSVGRenderer`      | 1                  | Renderer osztállyal egyben tesztelve |
| `ObserverTextRenderer`     | 1                  | Renderer osztállyal egyben tesztelve |
| `SVGRenderer` (absztrakt)  | -                  | Renderer osztállyal egyben tesztelve |
| `TextRenderer` (absztrakt) | -                  | Renderer osztállyal egyben tesztelve |

# Kód dokumentáció

| Teljesen dokumentált osztályok                                            | Részben dokumentált osztályok | Nem dokumentált osztályok |
| ------------------------------------------------------------------------- | ----------------------------- | ------------------------- |
| Minden osztály `./` és `./renderer` alatt és az össze publikus függvényük | -                             | -                         |

# Mindenféle számok

- Összes cpp kódsor : **1781**
- Összes header kódsor: **1895**
- Egyéb kódsor (make,doxyfile,shellscript, ...) : **4147**
- cppcheck
  - warning : **0**
  - style : **1**
  - performance : **0**
  - unusedFunction : **0**
  - missingInclude : **0**

# Implicit megtanult dolgok

- Container megfelelő és körültekintő használata
- SVG renderelés
- JSON fájlbeolvasás
- Megfelelő `sh` szkript írás a különböző tesztek és elleőrzések futtatásához

# Feedback (optional)

Véleményünk szerint kifejezetten jó volt az online videós megoldás. Habár előre nem volt tervezhető az egyes videők kijövetele, kifejezetten kényelmes volt, hogy akkor nézzük meg amikor az időnk engedi, így megfelelően tudtunk hozzákezdeni az anyag elsajátításához, illetve az videó követése és esetleg a videóval való együtt dolgozás is sokkal egyszerábbé vált.

Nagyon hasznosnak találtuk a GitHub-on adott hetente kijövő feladatokat és az ezzel kapcsolatos tanóra anyagához kapcsolodó fejlesztéseket, sokkal hasznosabb volt egy konkrét projektbe való különféle eszközök beépítése és ezeknek a tovább fejlesztése a projekttel együtt.

Én (@karcagtamas) magam a Github Actions használat, bemutatását találtam a leghasznosabb dolognak, a legtöbb dologgal már foglalkoztam korábban szoftverfejlesztői tanulmányaim és munkáim során, viszont az ilyes fél automatizmussal még nem foglalkoztam elötte. Szerintem kifejezetten hasznos volt.

# Üzenet a jövőbe (optional)

Nem igazán találtunk ide megfelelő gondolatot.

[More about the game and some attractive gif and video :D](https://mosze.apps.benswork.hu)
