 (*CPTS 355 LAB2*)

Control.Print.printDepth := 100;

fun map f [] = []
  | map f (x::rest) = (f x)::(map f rest);

fun fold f base [] = base
  | fold f base (x::rest) = f x (fold f base rest);

fun filter pred [] = []
  | filter pred (x::rest) =
		if pred x then x::(filter pred rest)
		else (filter pred rest);
		
fun filter2 pred [] = []
  | filter2 pred (x::rest) =
		if pred x = false then x::(filter2 pred rest)
		else (filter2 pred rest);
  
  
(*----------Problem 1----------*)
(*Part A: numbersToSum*)

fun numbersToSum n [] = []
  | numbersToSum n (x::rest) = 
		if n <= x then []
		else x::(numbersToSum (n-x) rest);

(*Part B: numbersToSumTail*)

fun sum [] = 0
  | sum (x::rest) = x + sum rest;

fun removeLast [x] = [] 
  | removeLast (x::rest) = x::(removeLast rest);

fun numbersToSumTail n [] = []
  | numbersToSumTail n (x::rest) = 
		if n > sum (x::rest) then (x::rest)
		else numbersToSumTail n (removeLast (x::rest));

(*----------Problem 2----------*)

fun exists n [] = false 
  | exists n (x::rest) = if n=x then true else (exists n rest);
  
fun partition F L = ((filter F L), (filter2 F L));

(*----------Problem 3----------*)

fun countInList [] x = 0 
  | countInList (y::rest) x = 
		if (x=y) then 1 + (countInList rest x)
		else countInList rest x;

fun areAllUnique [] = true
  | areAllUnique (x::rest) = 
		if [] = filter (fn x => (x>1)) (map (countInList (x::rest)) (x::rest))
			then true
		else false;

(*----------Problem 4----------*)
(*Part A: sum*)

fun add x y = x+y;

fun sum L = fold add 0 (map (fold add 0) L);

(*Part B: sumOption*)

datatype intOption = NONE | SOME of int;

fun addOption NONE NONE = NONE
  | addOption NONE (SOME x) = SOME x
  | addOption (SOME x) NONE = SOME x
  | addOption (SOME x) (SOME y) = SOME (x+y);
  
fun sumOption L = fold addOption NONE (map (fold addOption NONE) L);

(*Part C: sumEither*)

datatype either = IString of string | IInt of int;

fun str2int s = valOf(Int.fromString(s));

fun addEither (IInt x) (IInt y) = IInt (x+y)
  | addEither (IString x) (IInt y) = IInt ((str2int x) + y)
  | addEither (IInt x) (IString y) = IInt (x + (str2int y))
  | addEither (IString x) (IString y) = IInt ((str2int x) + (str2int y));
  
fun sumEither L = fold addEither (IInt 0) (map (fold addEither (IInt 0)) L);

(*----------Problem 5----------*)

datatype 'a Tree = LEAF of 'a | NODE of 'a * ('a Tree) * ('a Tree);

val T1 = NODE(1, NODE (2, NODE(3, LEAF 2 ,LEAF 5),LEAF 1), NODE(1,LEAF 8,LEAF 5));
val T2 = NODE(1, NODE (2, NODE(4, LEAF 8 ,LEAF 9),NODE(5, LEAF 10, LEAF 11)), NODE(3,LEAF 6,LEAF 7));
val T3 = NODE(2, NODE (4, NODE(8, LEAF 16 ,LEAF 18),NODE(10, LEAF 20, LEAF 22)), NODE(6, NODE(12, LEAF 24, LEAF 26), LEAF 14));
val T4 = NODE(1, NODE (3, NODE(3, LEAF 7, LEAF 3),LEAF 5), NODE(1,LEAF 9,LEAF 5));

(*Part A: depthScan*)

fun depthScan (LEAF x) = [x]
  | depthScan (NODE (tree, left, right)) = (depthScan left) @ (depthScan right) @ [tree];

(*Part B: depthSearch*)
(*
fun helper (LEAF x) level v = if (v = x) then level else 1;
  | helper (NODE(y, L, R)) level v = 
			if ((helper L (level+1) v) >= 0) then (helper L (level+1) v)
			else if ((helper R (level+1) v) >= 0) then (helper R (level+1) v)
			else if (y = v) then level else ~1;
			
fun depthSearch Tree v = helper Tree 1 v;
*)
(*Part C: addTrees*)

fun createTree (LEAF(v)) = LEAF (v)
  | createTree (NODE(v,t1,t2)) = (NODE (v, (createTree t1), (createTree t2)));

fun addTrees (LEAF x) (LEAF y) = LEAF (x+y)
  | addTrees (LEAF x) (NODE (y, l2, r2)) = (NODE(x+y, (createTree l2), (createTree r2)))
  | addTrees (NODE (x, l1, r1)) (LEAF y) = (NODE(x+y, (createTree l1), (createTree r1)))
  | addTrees (NODE (x, l1, r1)) (NODE (y, l2, r2)) = (NODE(x+y, (addTrees l1 l2), (addTrees r1 r2)));

  
(*----------------------------------------------------------------------------------------------------*)
  
  
(*----------Problem 1----------*)
(*Part A: numbersToSum*)

fun numbersToSumTest() = 
let
			
	val numbersToSumT1 = ((numbersToSum 100 [10, 20, 30, 40]) = ([10, 20, 30]))
	val numbersToSumT2 = ((numbersToSum 30 [5, 4, 6, 10, 4, 2, 1, 5]) = ([5, 4, 6, 10, 4]))
	val numbersToSumT3 = ((numbersToSum 1 [2]) = ([]))
	val numbersToSumT4 = ((numbersToSum 1 []) = ([]))

in
	print ("\nProblem 1-A\n\nnumbersToSum:-------------------- \n" ^
		" test1: " ^ Bool.toString(numbersToSumT1) ^ "\n" ^
		" test2: " ^ Bool.toString(numbersToSumT2) ^ "\n" ^
		" test3: " ^ Bool.toString(numbersToSumT3) ^ "\n" ^
		" test4: " ^ Bool.toString(numbersToSumT4) ^ "\n")
end 

val _ = numbersToSumTest();


(*Part B: numbersToSumTail*)

fun numbersToSumTailTest() = 
let
			
	val numbersToSumTailT1 = ((numbersToSumTail 100 [10, 20, 30, 40]) = ([10, 20, 30]))
	val numbersToSumTailT2 = ((numbersToSumTail 30 [5, 4, 6, 10, 4, 2, 1, 5]) = ([5, 4, 6, 10, 4]))
	val numbersToSumTailT3 = ((numbersToSumTail 1 [2]) = ([]))
	val numbersToSumTailT4 = ((numbersToSumTail 1 []) = ([]))

in
	print ("\nProblem 1-B\n\nnumbersToSumTail:-------------------- \n" ^
		" test1: " ^ Bool.toString(numbersToSumTailT1) ^ "\n" ^
		" test2: " ^ Bool.toString(numbersToSumTailT2) ^ "\n" ^
		" test3: " ^ Bool.toString(numbersToSumTailT3) ^ "\n" ^
		" test4: " ^ Bool.toString(numbersToSumTailT4) ^ "\n")
end 

val _ = numbersToSumTailTest();


(*----------Problem 2----------*)

fun partitionTest() = 
let
			
	val partitionT1 = ((partition (fn x => (x<=4)) [1,7,4,5,3,8,2,3]) = ([1,4,3,2,3],[7,5,8]))
	val partitionT2 = ((partition null [[1,2],[1],[],[5],[],[6,7,8]]) = ([[],[]],[[1,2],[1],[5],[6,7,8]]))
	val partitionT3 = ((partition (exists 1) [[1,2],[1],[],[5],[],[6,7,8]]) = ([[1,2],[1]],[[],[5],[],[6,7,8]]))
	val partitionT4 = ((partition (fn x=> (x<=4)) []) = ([],[]))

in
	print ("\nProblem 2\n\npartitionTest:-------------------- \n" ^
		" test1: " ^ Bool.toString(partitionT1) ^ "\n" ^
		" test2: " ^ Bool.toString(partitionT2) ^ "\n" ^
		" test3: " ^ Bool.toString(partitionT3) ^ "\n" ^
		" test4: " ^ Bool.toString(partitionT4) ^ "\n")
end 

val _ = partitionTest();

(*----------Problem 3----------*)

fun areAllUniqueTest() = 
let
			
	val areAllUniqueT1 = ((areAllUnique [1,3,4,2,5,0,10]) = true)
	val areAllUniqueT2 = ((areAllUnique [[1,2],[3],[4,5],[]]) = true)
	val areAllUniqueT3 = ((areAllUnique [(1,"one"),(2,"two"),(1,"one")]) = false)
	val areAllUniqueT4 = ((areAllUnique []) = true)
	val areAllUniqueT5 = ((areAllUnique [1,2,3,4,1,7]) = false)

in
	print ("\nProblem 3\n\nareAllUnique:-------------------- \n" ^
		" test1: " ^ Bool.toString(areAllUniqueT1) ^ "\n" ^
		" test2: " ^ Bool.toString(areAllUniqueT2) ^ "\n" ^
		" test3: " ^ Bool.toString(areAllUniqueT3) ^ "\n" ^
		" test4: " ^ Bool.toString(areAllUniqueT4) ^ "\n" ^
		" test5: " ^ Bool.toString(areAllUniqueT5) ^ "\n")
end 

val _ = areAllUniqueTest();

(*----------Problem 4----------*)
(*Part A: sum*)

fun sumTest() = 
let
			
	val sumT1 = ((sum [[1,2,3],[4,5],[6,7,8,9],[]]) = 45)
	val sumT2 = ((sum [[10,10],[10,10,10],[10]]) = 60)
	val sumT3 = ((sum [[]]) = 0)
	val sumT4 = ((sum []) = 0)

in
	print ("\nProblem 4-A\n\nsum:-------------------- \n" ^
		" test1: " ^ Bool.toString(sumT1) ^ "\n" ^
		" test2: " ^ Bool.toString(sumT2) ^ "\n" ^
		" test3: " ^ Bool.toString(sumT3) ^ "\n" ^
		" test4: " ^ Bool.toString(sumT4) ^ "\n")
end 

val _ = sumTest();

(*Part B: sumOption*)

fun sumOptionTest() = 
let
			
	val sumOptionT1 = ((sumOption [[SOME(1),SOME(2),SOME(3)],[SOME(4),SOME(5)],[SOME(6),NONE],[],[NONE]]) = (SOME 21))
	val sumOptionT2 = ((sumOption [[SOME(10),NONE],[SOME(10), SOME(10), SOME(10),NONE,NONE]]) = (SOME 40))
	val sumOptionT3 = ((sumOption [[NONE]]) = (NONE))
	val sumOptionT4 = ((sumOption []) = (NONE))

in
	print ("\nProblem 4-B\n\nsumOption:-------------------- \n" ^
		" test1: " ^ Bool.toString(sumOptionT1) ^ "\n" ^
		" test2: " ^ Bool.toString(sumOptionT2) ^ "\n" ^
		" test3: " ^ Bool.toString(sumOptionT3) ^ "\n" ^
		" test4: " ^ Bool.toString(sumOptionT4) ^ "\n")
end 

val _ = sumOptionTest();

(*Part C: sumEither*)

fun sumEitherTest() = 
let
			
	val sumEitherT1 = ((sumEither [[IString "1",IInt 2,IInt 3],[IString "4",IInt 5],[IInt 6,IString "7"],[],[IString "8"]]) = IInt 36)
	val sumEitherT2 = ((sumEither [[IString "10" , IInt 10],[],[IString "10"],[]]) = IInt 30)
	val sumEitherT3 = ((sumEither [[]] ) = IInt 0)

in
	print ("\nProblem 4-C\n\nsumEither:-------------------- \n" ^
		" test1: " ^ Bool.toString(sumEitherT1) ^ "\n" ^
		" test2: " ^ Bool.toString(sumEitherT2) ^ "\n" ^
		" test3: " ^ Bool.toString(sumEitherT3) ^ "\n")
end 

val _ = sumEitherTest();


(*----------Problem 5----------*)
(*Part A: depthScan*)

fun depthScanTest() = 
let
			
	val depthScanT1 = ((depthScan (NODE("Science",NODE ("and",LEAF "School", NODE("Engineering", LEAF "of"
                    	,LEAF "Electrical")),LEAF "Computer"))) = (["School","of","Electrical","Engineering","and","Computer","Science"]))
	val depthScanT2 = ((depthScan (NODE(1, NODE (2, NODE(3, LEAF 4 ,LEAF 5),LEAF 6), NODE(7,LEAF 8,LEAF 9)))) = 
						([4,5,3,6,2,8,9,7,1]))
	val depthScanT3 = ((depthScan (LEAF 4)) = ([4]))
	val depthScanT4 = ((depthScan T1) = [2,5,3,1,2,8,5,1,1])
	val depthScanT5 = ((depthScan T4) = [7,3,3,5,3,9,5,1,1])

in
	print ("\nProblem 5-A\n\ndepthScanTest:-------------------- \n" ^
		" test1: " ^ Bool.toString(depthScanT1) ^ "\n" ^
		" test2: " ^ Bool.toString(depthScanT2) ^ "\n" ^
		" test3: " ^ Bool.toString(depthScanT3) ^ "\n" ^
		" test4: " ^ Bool.toString(depthScanT4) ^ "\n" ^
		" test5: " ^ Bool.toString(depthScanT5) ^ "\n")
end 

val _ = depthScanTest();

(*Part B: depthSearch*)
(*
fun depthSearchTest() = 
let
			
	val depthSearchT1 = ((depthSearch T1 1) = 3)
	val depthSearchT2 = ((depthSearch T1 5) = 4)
	val depthSearchT3 = ((depthSearch T1 8) = 3)
	val depthSearchT4 = ((depthSearch T1 4) = ~1)
	val depthSearchT5 = ((depthSearch T2 10) = 4)
	val depthSearchT6 = ((depthSearch T3 18) = 4)
in
	print ("\nProblem 5-B\n\ndepthSearch:-------------------- \n" ^
		" test1: " ^ Bool.toString(depthSearchT1) ^ "\n" ^
		" test2: " ^ Bool.toString(depthSearchT2) ^ "\n" ^
		" test3: " ^ Bool.toString(depthSearchT3) ^ "\n" ^
		" test4: " ^ Bool.toString(depthSearchT4) ^ "\n" ^
		" test5: " ^ Bool.toString(depthSearchT5) ^ "\n" ^
		" test6: " ^ Bool.toString(depthSearchT6) ^ "\n")
end 

val _ = depthSearchTest();
*)
(*Part C: addTrees*)

fun addTreesTest() = 
let
			
	val addTreesT1 = (depthScan(addTrees T1 T2) = [10,14,7,10,11,6,4,14,12,4,2])
	val addTreesT2 = (depthScan(addTrees T2 T1) = [10,14,7,10,11,6,4,14,12,4,2])
	val addTreesT3 = (depthScan(addTrees T1 T4) = [9,8,6,6,5,17,10,2,2])
	val addTreesT4 = (depthScan(addTrees T4 T1) = [9,8,6,6,5,17,10,2,2])
	val addTreesT5 = (depthScan(addTrees T2 T4) = [15,12,7,10,11,10,5,15,12,4,2])
	val addTreesT6 = (depthScan(addTrees T4 T2) = [15,12,7,10,11,10,5,15,12,4,2])
in
	print ("\nProblem 5-C\n\naddTrees:-------------------- \n" ^
		" test1: " ^ Bool.toString(addTreesT1) ^ "\n" ^
		" test2: " ^ Bool.toString(addTreesT2) ^ "\n" ^
		" test3: " ^ Bool.toString(addTreesT3) ^ "\n" ^
		" test4: " ^ Bool.toString(addTreesT4) ^ "\n" ^
		" test5: " ^ Bool.toString(addTreesT5) ^ "\n" ^
		" test6: " ^ Bool.toString(addTreesT6) ^ "\n")
end 

val _ = addTreesTest();
