(define (domain kitchen)
  (:requirements :typing :action-costs)
  (:types
        noodles - ingredient
        ingredient content - food
        roastingTin bakingTray - stoveDish
        cookingPot pan bowl stoveDish - dish
        food dish - object
  )

  (:constants 
      water onion garlic oil mincedMeat tomatoes bacon parmesan cream eggs chili tomatoPaste tomatoJuice cremeFraiche milk custardPowder sugar lettuce rocket mozzarella vinegar balsamicVinegar oliveOil mustard potatoes beans salt pepper paprika pea rice trout butter chicken pork beef flour breadcrumbs vanillaIce raspberry mascarpone curd vanillaSugar almondBiscuit oregano yoghurt ciabatta carrot - ingredient
  )

  (:predicates
     (contentOf ?d - dish ?c - content)
  )

  (:task mtlt :parameters ())
  (:task makeStarter :parameters ())
  (:task makeMain :parameters ())
  (:task makeDessert :parameters ())

  ;; starters
  (:task makeTomatoSoup :parameters (?p - cookingPot))
  (:task makeLettuce :parameters (?b - bowl))
  (:task makeTomatoMozzarella :parameters (?b - bowl))
  (:task makeBruchetta :parameters ())
  (:task makeCarrotSoup :parameters (?p - cookingPot))

  ;; main dishes
  (:task makeNoodles :parameters (?n - noodles ?p - cookingPot))
  (:task makeBolognese :parameters (?p - pan))
  (:task makeCarbonara :parameters (?p - pan))
  (:task makeAllArrabbiata :parameters (?p - cookingPot))
  (:task makeBoiledPotatoes :parameters (?p - cookingPot))
  (:task makeSkinnedPotatoes :parameters (?p - cookingPot))
  (:task makeRice :parameters (?p - cookingPot))
  (:task makeTrout :parameters (?p - pan))
  (:task makeChicken :parameters (?r - roastingTin))
  (:task makeSchnitzel :parameters (?p - pan))
  (:task makeBeans :parameters (?p - cookingPot))
  (:task makePea :parameters (?p - cookingPot))

  ;; desserts
  (:task makeVanillaPudding :parameters (?p - cookingPot))
  (:task makeVanillaRaspberryIce :parameters (?b - bowl))
  (:task makeTiramisu :parameters (?b - bowl))
  (:task makeMascarpone :parameters (?b - bowl))
  (:task makePancakes :parameters (?p - pan))

;;
;; generator methods
;;

  (:method generator-1
    :parameters ()
    :task (mtlt)
    :subtasks (and
       (makeMain)
       )
  )

  (:method generator-2
    :parameters ()
    :task (mtlt)
    :subtasks (and
       (makeStarter)
       (makeMain)
       )
  )

  (:method generator-3
    :parameters ()
    :task (mtlt)
    :subtasks (and
       (makeMain)
       (makeDessert)
       )
  )

  (:method generator-4
    :parameters ()
    :task (mtlt)
    :subtasks (and
       (makeStarter)
       (makeMain)
       (makeDessert)
       )
  )

  (:method starter-1
    :parameters (?pot1 - cookingPot)
    :task (makeStarter)
    :subtasks (and
       (makeTomatoSoup ?pot1)
       )
  )

  (:method starter-2
    :parameters (?bowl1 - bowl)
    :task (makeStarter)
    :subtasks (and
       (makeLettuce ?bowl1)
       )
  )

  (:method starter-3
    :parameters (?bowl1 - bowl)
    :task (makeStarter)
    :subtasks (and
       (makeTomatoMozzarella ?bowl1)
       )
  )

  (:method starter-4
    :parameters ()
    :task (makeStarter)
    :subtasks (and
       (makeBruchetta)
       )
  )

  (:method starter-5
    :parameters (?pot1 - cookingPot)
    :task (makeStarter)
    :subtasks (and
       (makeCarrotSoup ?pot1)
       )
  )

  (:method main-1
    :parameters (?pot1 - cookingPot ?pan1 - pan)
    :task (makeMain)
    :subtasks (and
       (makeNoodles spaghetti ?pot1)
       (makeBolognese ?pan1)
       )
  )

  (:method main-2
    :parameters (?pot1 - cookingPot ?pan1 - pan)
    :task (makeMain)
    :subtasks (and
       (makeNoodles spaghetti ?pot1)
       (makeCarbonara ?pan1)
       )
  )

  (:method main-3
    :parameters (?pot1 - cookingPot ?pot2 - cookingPot)
    :task (makeMain)
    :subtasks (and
       (makeNoodles spaghetti ?pot1)
       (makeAllArrabbiata ?pot2)
       )
  )

  (:method main-4
    :parameters (?pot1 - cookingPot ?pan1 - pan)
    :task (makeMain)
    :subtasks (and
       (makeNoodles cannelloni ?pot1)
       (makeBolognese ?pan1)
       )
  )

  (:method main-5
    :parameters (?pot1 - cookingPot ?pan1 - pan)
    :task (makeMain)
    :subtasks (and
       (makeNoodles cannelloni ?pot1)
       (makeCarbonara ?pan1)
       )
  )

  (:method main-6
    :parameters (?pot1 - cookingPot ?pot2 - cookingPot)
    :task (makeMain)
    :subtasks (and
       (makeNoodles cannelloni ?pot1)
       (makeAllArrabbiata ?pot2)
       )
  )

  (:method main-7
    :parameters (?pot1 - cookingPot ?pan1 - pan)
    :task (makeMain)
    :subtasks (and
       (makeNoodles tortellini ?pot1)
       (makeBolognese ?pan1)
       )
  )

  (:method main-8
    :parameters (?pot1 - cookingPot ?pan1 - pan)
    :task (makeMain)
    :subtasks (and
       (makeNoodles tortellini ?pot1)
       (makeCarbonara ?pan1)
       )
  )

  (:method main-9
    :parameters (?pot1 - cookingPot ?pot2 - cookingPot)
    :task (makeMain)
    :subtasks (and
       (makeNoodles tortellini ?pot1)
       (makeAllArrabbiata ?pot2)
       )
  )

  (:method main-10
    :parameters (?pot1 - cookingPot ?pan1 - pan)
    :task (makeMain)
    :subtasks (and
       (makeNoodles ravioli ?pot1)
       (makeBolognese ?pan1)
       )
  )

  (:method main-11
    :parameters (?pot1 - cookingPot ?pan1 - pan)
    :task (makeMain)
    :subtasks (and
       (makeNoodles ravioli ?pot1)
       (makeCarbonara ?pan1)
       )
  )

  (:method main-12
    :parameters (?pot1 - cookingPot ?pot2 - cookingPot)
    :task (makeMain)
    :subtasks (and
       (makeNoodles ravioli ?pot1)
       (makeAllArrabbiata ?pot2)
       )
  )

  (:method main-13
    :parameters (?pot1 - cookingPot ?pan1 - pan ?pot2 - cookingPot)
    :task (makeMain)
    :subtasks (and
       (makeBoiledPotatoes ?pot1)
       (makeTrout ?pan1)
       (makeBeans ?pot2)
       )
  )

  (:method main-14
    :parameters (?pot1 - cookingPot ?rt1 - roastingTin ?pot2 - cookingPot)
    :task (makeMain)
    :subtasks (and
       (makeBoiledPotatoes ?pot1)
       (makeChicken ?rt1)
       (makeBeans ?pot2)
       )
  )

  (:method main-15
    :parameters (?pot1 - cookingPot ?pan1 - pan ?pot2 - cookingPot)
    :task (makeMain)
    :subtasks (and
       (makeBoiledPotatoes ?pot1)
       (makeSchnitzel ?pan1)
       (makeBeans ?pot2)
       )
  )

  (:method main-16
    :parameters (?pot1 - cookingPot ?pan1 - pan ?pot2 - cookingPot)
    :task (makeMain)
    :subtasks (and
       (makeBoiledPotatoes ?pot1)
       (makeTrout ?pan1)
       (makePea ?pot2)
       )
  )

  (:method main-17
    :parameters (?pot1 - cookingPot ?rt1 - roastingTin ?pot2 - cookingPot)
    :task (makeMain)
    :subtasks (and
       (makeBoiledPotatoes ?pot1)
       (makeChicken ?rt1)
       (makePea ?pot2)
       )
  )

  (:method main-18
    :parameters (?pot1 - cookingPot ?pan1 - pan ?pot2 - cookingPot)
    :task (makeMain)
    :subtasks (and
       (makeBoiledPotatoes ?pot1)
       (makeSchnitzel ?pan1)
       (makePea ?pot2)
       )
  )

  (:method main-19
    :parameters (?pot1 - cookingPot ?pan1 - pan ?pot2 - cookingPot)
    :task (makeMain)
    :subtasks (and
       (makeSkinnedPotatoes ?pot1)
       (makeTrout ?pan1)
       (makeBeans ?pot2)
       )
  )

  (:method main-20
    :parameters (?pot1 - cookingPot ?rt1 - roastingTin ?pot2 - cookingPot)
    :task (makeMain)
    :subtasks (and
       (makeSkinnedPotatoes ?pot1)
       (makeChicken ?rt1)
       (makeBeans ?pot2)
       )
  )

  (:method main-21
    :parameters (?pot1 - cookingPot ?pan1 - pan ?pot2 - cookingPot)
    :task (makeMain)
    :subtasks (and
       (makeSkinnedPotatoes ?pot1)
       (makeSchnitzel ?pan1)
       (makeBeans ?pot2)
       )
  )

  (:method main-22
    :parameters (?pot1 - cookingPot ?pan1 - pan ?pot2 - cookingPot)
    :task (makeMain)
    :subtasks (and
       (makeSkinnedPotatoes ?pot1)
       (makeTrout ?pan1)
       (makePea ?pot2)
       )
  )

  (:method main-23
    :parameters (?pot1 - cookingPot ?rt1 - roastingTin ?pot2 - cookingPot)
    :task (makeMain)
    :subtasks (and
       (makeSkinnedPotatoes ?pot1)
       (makeChicken ?rt1)
       (makePea ?pot2)
       )
  )

  (:method main-24
    :parameters (?pot1 - cookingPot ?pan1 - pan ?pot2 - cookingPot)
    :task (makeMain)
    :subtasks (and
       (makeSkinnedPotatoes ?pot1)
       (makeSchnitzel ?pan1)
       (makePea ?pot2)
       )
  )

  (:method main-25
    :parameters (?pot1 - cookingPot ?pan1 - pan ?pot2 - cookingPot)
    :task (makeMain)
    :subtasks (and
       (makeRice ?pot1)
       (makeTrout ?pan1)
       (makeBeans ?pot2)
       )
  )

  (:method main-26
    :parameters (?pot1 - cookingPot ?rt1 - roastingTin ?pot2 - cookingPot)
    :task (makeMain)
    :subtasks (and
       (makeRice ?pot1)
       (makeChicken ?rt1)
       (makeBeans ?pot2)
       )
  )

  (:method main-27
    :parameters (?pot1 - cookingPot ?pan1 - pan ?pot2 - cookingPot)
    :task (makeMain)
    :subtasks (and
       (makeRice ?pot1)
       (makeSchnitzel ?pan1)
       (makeBeans ?pot2)
       )
  )

  (:method main-28
    :parameters (?pot1 - cookingPot ?pan1 - pan ?pot2 - cookingPot)
    :task (makeMain)
    :subtasks (and
       (makeRice ?pot1)
       (makeTrout ?pan1)
       (makePea ?pot2)
       )
  )

  (:method main-29
    :parameters (?pot1 - cookingPot ?rt1 - roastingTin ?pot2 - cookingPot)
    :task (makeMain)
    :subtasks (and
       (makeRice ?pot1)
       (makeChicken ?rt1)
       (makePea ?pot2)
       )
  )

  (:method main-30
    :parameters (?pot1 - cookingPot ?pan1 - pan ?pot2 - cookingPot)
    :task (makeMain)
    :subtasks (and
       (makeRice ?pot1)
       (makeSchnitzel ?pan1)
       (makePea ?pot2)
       )
  )

  (:method dessert-1
    :parameters (?pot1 - cookingPot)
    :task (makeDessert)
    :subtasks (and
       (makeVanillaPudding ?pot1)
       )
  )

  (:method dessert-2
    :parameters (?bowl1 - bowl)
    :task (makeDessert)
    :subtasks (and
       (makeVanillaRaspberryIce ?bowl1)
       )
  )

  (:method dessert-3
    :parameters (?bowl1 - bowl)
    :task (makeDessert)
    :subtasks (and
       (makeTiramisu ?bowl1)
       )
  )

  (:method dessert-4
    :parameters (?bowl1 - bowl)
    :task (makeDessert)
    :subtasks (and
       (makeMascarpone ?bowl1)
       )
  )

  (:method dessert-5
    :parameters (?pan1 - pan)
    :task (makeDessert)
    :subtasks (and
       (makePancakes ?pan1)
       )
  )

;;
;; starters
;;

  (:method m-makeTomatoMozzarella
    :parameters (?b - bowl)
    :task (makeTomatoMozzarella ?b)
    :subtasks (and
       (st1 (slice mozzarella))
       (st2 (slice tomatoes))
       (st3 (add mozzarella ?b))
       (st4 (add tomatoes ?b))
       (st5 (add oliveOil ?b))
       (st6 (add balsamicVinegar ?b))
       (st7 (add oregano ?b))
       (st8 (add salt ?b))
       (st9 (add pepper ?b))
    )
    :ordering (and
       (st1 < st3)
       (st2 < st4)
       (st3 < st5)
       (st4 < st5)
       (st3 < st6)
       (st4 < st6)
       (st3 < st7)
       (st4 < st7)
       (st3 < st8)
       (st4 < st8)
       (st3 < st9)
       (st4 < st9)
    )
  )

  (:method m-makeTomatoSoup
    :parameters (?p - cookingPot)
    :task (makeTomatoSoup ?p)
    :subtasks (and
       (st1 (chop bacon))
       (st2 (add oil ?p))
       (st3 (roast oil ?p))
       (st4 (add bacon ?p))
       (st5 (roast bacon ?p))
       (st6 (chop onion))
       (st7 (add onion ?p))
       (st8 (roast onion ?p))
       (st9 (add tomatoes ?p))
       (st10 (cook tomatoes ?p))
       (st11 (add cremeFraiche ?p))
    )
    :ordering (and
       (st1 < st4)
       (st2 < st3)
       (st3 < st4)
       (st4 < st5)
       (st6 < st7)
       (st7 < st8)
       (st8 < st9)
       (st9 < st10)
       (st10 < st11)
    )
  )

  (:method m-makeCarrotSoup
    :parameters (?p - cookingPot ?c - content)
    :task (makeCarrotSoup ?p)
    :precondition (and
       (contentOf ?p ?c)
    )
    :subtasks (and
       (st1 (chop onion))
       (st2 (add oil ?p))
       (st3 (roast oil ?p))
       (st4 (add onion ?p))
       (st5 (roast onion ?p))
       (st6 (chop carrot))
       (st7 (add carrot ?p))
       (st8 (chop potatoes))
       (st9 (add potatoes ?p))
       (st10 (chop garlic))
       (st11 (add garlic ?p))
       (st12 (add pepper ?p))
       (st13 (add water ?p))
       (st14 (cook ?c ?p))
       (st15 (add cream ?p))
       (st16 (puree ?c ?p))
    )
    :ordering (and
       (st1 < st4)
       (st2 < st3)
       (st3 < st4)
       (st4 < st5)
       (st6 < st7)
       (st8 < st9)
       (st10 < st11)
       (st5 < st7)
       (st5 < st9)
       (st5 < st11)
       (st5 < st12)
       (st5 < st13)
       (st7 < st14)
       (st9 < st14)
       (st11 < st14)
       (st12 < st14)
       (st13 < st14)
    )
  )

  (:method m-makeLettuce
    :parameters (?b - bowl ?b2 - bowl ?c - content)
    :task (makeLettuce ?b)
    :precondition (and
       (not(= ?b ?b2))
       (contentOf ?b2 ?c)
    )
    :subtasks (and
       (st1 (wash lettuce))
       (st2 (wash rocket))
       (st3 (add lettuce ?b))
       (st4 (add rocket ?b))
       (st5 (add tomatoes ?b))
       (st6 (add oliveOil ?b2))
       (st7 (add vinegar ?b2))
       (st8 (add mustard ?b2))
       (st9 (mix ?c))
       (st10 (add ?c ?b))
    )
    :ordering (and
       (st1 < st3)
       (st2 < st4)
       (st3 < st10)
       (st4 < st10)
       (st5 < st10)
       (st6 < st9)
       (st7 < st9)
       (st8 < st9)
       (st9 < st10)
    )
  )

  (:method m-makeBruchetta
    :parameters (?b - bowl ?t - bakingTray ?c - content)
    :task (makeBruchetta)
    :precondition(and
       (contentOf ?b ?c)
    )
    :subtasks (and
       (st1 (chop tomatoes))
       (st2 (chop garlic))
       (st3 (add tomatoes ?b))
       (st4 (add oliveOil ?b))
       (st5 (add salt ?b))
       (st6 (add garlic ?b))
       (st7 (mix ?c))
       (st8 (add ciabatta ?t))
       (st9 (bake ciabatta ?t))
       (st10 (slice ciabatta))
       (st11 (sprinkle ?c ciabatta))
    )
    :ordering (and
       (st1 < st3)
       (st2 < st6)
       (st3 < st7)
       (st4 < st7)
       (st5 < st7)
       (st6 < st7)
       (st7 < st11)
       (st8 < st9)
       (st9 < st10)
       (st10 < st11)
    )
  )

;;
;; main dishes
;;

  (:method m-makeNoodles
    :parameters (?n - noodles ?p - cookingPot)
    :task (makeNoodles ?n ?p)
    :ordered-subtasks (and
       (add water ?p)
       (cook water ?p)
       (add ?n ?p)
       (add salt ?p)
       (add oil ?p)
       (cook ?n ?p)
       (drain ?n ?p)
    )
  )

  (:method m-makeBolognese
    :parameters (?p - pan)
    :task (makeBolognese ?p)
    :subtasks (and
       (st1 (chop onion))
       (st2 (chop garlic))
       (st3 (add oil ?p))
       (st4 (roast oil ?p))
       (st5 (add onion ?p))
       (st6 (add garlic ?p))
       (st7 (roast onion ?p))
       (st8 (roast garlic ?p))
       (st9 (add mincedMeat ?p))
       (st10 (roast mincedMeat ?p))
       (st11 (add tomatoes ?p))
       (st12 (cook tomatoes ?p))
    )
    :ordering (and
       (st3 < st4)
       (st4 < st5)
       (st4 < st6)
       (st1 < st5)
       (st2 < st6)
       (st5 < st7)
       (st6 < st8)
       (st7 < st9)
       (st8 < st9)
       (st9 < st10)
       (st10 < st11)
       (st11 < st12)
    )
  )

  (:method m-makeCarbonara
    :parameters (?p - pan ?b - bowl ?c - content)
    :task (makeCarbonara ?p)
    :precondition (and
       (contentOf ?b ?c)
    )
    :subtasks (and
       (st1 (chop bacon))
       (st2 (add oil ?p))
       (st3 (roast oil ?p))
       (st4 (add bacon ?p))
       (st5 (roast bacon ?p))
       (st6 (add eggs ?b))
       (st7 (add parmesan ?b))
       (st8 (add cream ?b))
       (st9 (mix ?c))
       (st10 (add ?c ?p))
       (st11 (cook eggs ?p))
    )
    :ordering (and
       (st1 < st4)
       (st2 < st3)
       (st3 < st4)
       (st4 < st5)
       (st5 < st10)
       (st6 < st9)
       (st7 < st9)
       (st8 < st9)
       (st9 < st10)
       (st10 < st11)
    )
  )
  
  (:method m-makeAllArrabbiata
    :parameters (?p - cookingPot)
    :task (makeAllArrabbiata ?p)
    :subtasks (and
       (st1 (chop onion))
       (st2 (chop garlic))
       (st3 (add oil ?p))
       (st4 (roast oil ?p))
       (st5 (add onion ?p))
       (st6 (add garlic ?p))
       (st7 (roast onion ?p))
       (st8 (roast garlic ?p))
       (st9 (chop chili))
       (st10 (add chili ?p))
       (st11 (add tomatoPaste ?p))
       (st12 (roast chili ?p))
       (st13 (roast tomatoPaste ?p))
       (st14 (add tomatoJuice ?p))
       (st15 (cook tomatoJuice ?p))
    )
    :ordering (and
       (st3 < st4)
       (st4 < st5)
       (st4 < st6)
       (st1 < st5)
       (st2 < st6)
       (st5 < st7)
       (st6 < st8)
       (st9 < st10)
       (st10 < st11)
       (st11 < st12)
       (st11 < st13)
       (st13 < st14)
       (st14 < st15)
    )
  )

  (:method m-makeBoiledPotatoes
    :parameters (?p - cookingPot)
    :task (makeBoiledPotatoes ?p)
    :ordered-subtasks (and
       (peel potatoes)
       (add potatoes ?p)
       (add water ?p)
       (cook potatoes ?p)
    )
  )

  (:method m-makeSkinnedPotatoes
    :parameters (?p - cookingPot)
    :task (makeSkinnedPotatoes ?p)
    :ordered-subtasks (and
       (skin potatoes)
       (add potatoes ?p)
       (add water ?p)
       (cook potatoes ?p)
    )
  )

  (:method m-makeChicken
    :parameters (?t - roastingTin ?c - content)
    :task (makeChicken ?t)
    :precondition (and
       (contentOf ?t ?c)
    )
    :subtasks (and
       (st1 (wash chicken))
       (st2 (add chicken ?t))
       (st3 (add paprika ?t))
       (st4 (add salt ?t))
       (st5 (add oil ?t))
       (st6 (bake ?c ?t))
    )
    :ordering (and
       (st1 < st2)
       (st2 < st3)
       (st2 < st4)
       (st2 < st5)
       (st3 < st6)
       (st4 < st6)
       (st5 < st6)
    )
  )

  (:method m-makeSchnitzel1
    :parameters (?t - pan)
    :task (makeSchnitzel ?t)
    :subtasks (and
       (st1 (flatten pork))
       (st2 (sprinkle salt pork))
       (st3 (sprinkle pepper pork))
       (st4 (sprinkle eggs pork))
       (st5 (sprinkle flour pork))
       (st6 (sprinkle breadcrumbs pork))
       (st7 (add oil ?t))
       (st8 (roast pork ?t))
    )
    :ordering (and
       (st1 < st2)
       (st1 < st3)
       (st1 < st4)
       (st1 < st5)
       (st1 < st6)
       (st2 < st8)
       (st3 < st8)
       (st4 < st8)
       (st5 < st8)
       (st6 < st8)
       (st7 < st8)
    )
  )

  (:method m-makeSchnitzel2
    :parameters (?t - pan)
    :task (makeSchnitzel ?t)
    :subtasks (and
       (st1 (flatten beef))
       (st2 (sprinkle salt beef))
       (st3 (sprinkle pepper beef))
       (st4 (sprinkle eggs beef))
       (st5 (sprinkle flour beef))
       (st6 (sprinkle breadcrumbs beef))
       (st7 (add oil ?t))
       (st8 (roast beef ?t))
    )
    :ordering (and
       (st1 < st2)
       (st1 < st3)
       (st1 < st4)
       (st1 < st5)
       (st1 < st6)
       (st2 < st8)
       (st3 < st8)
       (st4 < st8)
       (st5 < st8)
       (st6 < st8)
       (st7 < st8)
    )
  )

  (:method m-makeTrout
    :parameters (?p - pan)
    :task (makeTrout ?p)
    :subtasks (and
       (st1 (wash trout))
       (st2 (add oil ?p))
       (st3 (roast oil ?p))
       (st4 (add trout ?p))
       (st5 (roast trout ?p))
       (st6 (turn trout ?p))
       (st7 (roast trout ?p))
       (st8 (add butter ?p))
       (st9 (roast butter ?p))
       (st10 (turn trout ?p))
    )
    :ordering (and
       (st1 < st4)
       (st2 < st3)
       (st3 < st4)
       (st4 < st5)
       (st5 < st6)
       (st6 < st7)
       (st7 < st8)
       (st8 < st9)
       (st9 < st10)
    )
  )

  (:method m-makeRice
    :parameters (?p - cookingPot)
    :task (makeRice ?p)
    :ordered-subtasks (and
       (add water ?p)
       (cook water ?p)
       (add rice ?p)
       (cook rice ?p)
    )
  )

  (:method m-makeBeans
    :parameters (?p - cookingPot)
    :task (makeBeans ?p)
    :ordered-subtasks (and
       (add water ?p)
       (cook water ?p)
       (add beans ?p)
       (cook beans ?p)
    )
  )

  (:method m-makePea
    :parameters (?p - cookingPot)
    :task (makePea ?p)
    :ordered-subtasks (and
       (add water ?p)
       (cook water ?p)
       (add pea ?p)
       (cook pea ?p)
    )
  )

;;
;; desserts
;;

  (:method m-makeVanillaPudding
    :parameters (?p - cookingPot)
    :task (makeVanillaPudding ?p)
    :subtasks (and
       (st1 (add milk ?p))
       (st2 (cook milk ?p))
       (st3 (add custardPowder ?p))
       (st4 (add sugar ?p))
       (st5 (cook milk ?p))
    )
    :ordering (and
       (st1 < st2)
       (st2 < st3)
       (st2 < st4)
       (st3 < st5)
       (st4 < st5)
    )
  )

  (:method m-makeVanillaRaspberryIce
    :parameters (?b - bowl)
    :task (makeVanillaRaspberryIce ?b)
    :subtasks (and
       (st1 (add vanillaIce ?b))
       (st2 (heat raspberry))
       (st3 (add raspberry ?b))
    )
    :ordering (and
       (st1 < st3)
       (st2 < st3)
    )
  )

  (:method m-makeTiramisu
    :parameters (?b1 ?b2 - bowl ?c1 ?c2 - content)
    :task (makeTiramisu ?b2)
    :precondition (and
       (contentOf ?b1 ?c1)
       (contentOf ?b2 ?c2)
    )
    :subtasks (and
       (st1 (add cream ?b1))
       (st2 (whip cream ?b1))
       (st3 (add mascarpone ?b1))
       (st4 (add curd ?b1))
       (st5 (add vanillaSugar ?b1))
       (st6 (add sugar ?b1))
       (st7 (mix ?c1))
       (st8 (add ?c1 ?b2))
       (st9 (add almondBiscuit ?b2))
       (st10 (add raspberry ?b2))
       (st11 (add ?c1 ?b2))
       (st12 (add almondBiscuit ?b2))
       (st13 (add raspberry ?b2))
       (st14 (add ?c1 ?b2))
       (st15 (cool ?c2))
    )
    :ordering (and
       (st1 < st2)
       (st2 < st3)
       (st2 < st4)
       (st2 < st5)
       (st2 < st6)
       (st3 < st7)
       (st4 < st7)
       (st5 < st7)
       (st6 < st7)
       (st7 < st8)
       (st8 < st9)
       (st9 < st10)
       (st10 < st11)
       (st11 < st12)
       (st12 < st13)
       (st13 < st14)
       (st14 < st15)
    )
  )

  (:method m-makeMascarpone
    :parameters (?b ?b1 ?b2 - bowl ?c ?c1 ?c2 - content)
    :task (makeMascarpone ?b)
    :precondition (and
       (not(= ?b ?b1))
       (not(= ?b ?b2))
       (not(= ?b1 ?b2))
       (contentOf ?b ?c)
       (contentOf ?b1 ?c1)
       (contentOf ?b2 ?c2)
    )
    :subtasks (and
       (st1 (add curd ?b1))
       (st2 (add yoghurt ?b1))
       (st3 (add mascarpone ?b1))
       (st4 (add sugar ?b1))
       (st5 (mix ?c1))
       (st6 (add cream ?b2))
       (st7 (whip cream ?b2))
       (st8 (add ?c2 ?b1))
       (st9 (mix ?c1))
       (st10 (add ?c1 ?b))
       (st11 (add raspberry ?b))
       (st12 (add ?c1 ?b))
       (st13 (add raspberry ?b))
       (st14 (add ?c1 ?b))
       (st15 (cool ?c))
    )
    :ordering (and
       (st1 < st5)
       (st2 < st5)
       (st3 < st5)
       (st4 < st5)
       (st6 < st7)
       (st7 < st8)
       (st8 < st9)
       (st9 < st10)
       (st10 < st11)
       (st11 < st12)
       (st12 < st13)
       (st13 < st14)
       (st14 < st15)
    )
  )

  (:method m-makePancakes
    :parameters (?p - pan ?b - bowl ?c - content)
    :task (makePancakes ?p)
    :precondition(and
       (contentOf ?b ?c)
    )
    :subtasks (and
       (st1 (add flour ?b))
       (st2 (add eggs ?b))
       (st3 (add salt ?b))
       (st4 (add sugar ?b))
       (st5 (add vanillaSugar ?b))
       (st6 (add milk ?b))
       (st7 (add water ?b))
       (st8 (mix ?c))
       (st9 (add oil ?p))
       (st10 (roast oil ?p))
       (st11 (add ?c ?p))
       (st12 (roast ?c ?p))
    )
    :ordering (and
       (st1 < st8)
       (st2 < st8)
       (st3 < st8)
       (st4 < st8)
       (st6 < st8)
       (st7 < st8)
       (st8 < st11)
       (st10 < st11)
    )
  )
 
;;
;; primitive cooking actions
;;

  (:action add
    :parameters (?f - food ?d - dish)
    :precondition ()
    :effect ()
  )
  
  (:action mix
    :parameters (?c - content)
    :precondition ()
    :effect ()
  )

  (:action turn
    :parameters (?f - food ?p - dish)
    :precondition ()
    :effect()
  )

  (:action cook
    :parameters (?f - food ?p - dish)
    :precondition ()
    :effect ()
  )

  (:action roast
    :parameters (?f - food ?p - dish)
    :precondition ()
    :effect()
  )

  (:action bake
    :parameters (?f - food ?sd - stoveDish)
    :precondition ()
    :effect()
  )

  (:action heat
    :parameters (?f - food)
    :precondition ()
    :effect ()
  )

  (:action cool
    :parameters (?f - food)
    :precondition ()
    :effect ()
  )

  (:action wash
    :parameters (?i - ingredient)
    :precondition ()
    :effect ()
  )

  (:action drain
    :parameters (?f - food ?p - dish)
    :precondition ()
    :effect ()
  )

  (:action chop
    :parameters (?i - ingredient)
    :precondition ()
    :effect ()
  )
  
  (:action slice
    :parameters (?i - ingredient)
    :precondition ()
    :effect ()
  )

  (:action puree
    :parameters (?f - food ?d - dish)
    :precondition ()
    :effect ()
  )

  (:action flatten
    :parameters (?i - ingredient)
    :precondition ()
    :effect ()
  )

  (:action peel
    :parameters (?i - ingredient)
    :precondition ()
    :effect ()
  )

  (:action skin
    :parameters (?i - ingredient)
    :precondition ()
    :effect ()
  )

  (:action whip
    :parameters (?i - ingredient ?d - dish)
    :precondition ()
    :effect ()
  )
  
  (:action sprinkle
    :parameters (?i - food ?f - food)
    :precondition ()
    :effect ()
  )
)