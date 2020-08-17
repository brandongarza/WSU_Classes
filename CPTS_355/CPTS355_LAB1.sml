print("\nCPTS355 Lab 1 - Brandon Garza\n\n");

(*--------Problem 1--------*)
(*Part A*)
	fun exists (x, []) = false 
		| exists (x, y::rest) = 
			if (x=y) then true 
			else exists(x, rest);

fun existsTest() = 
let
			
	val existsT1 = ((exists (1,[])) = false)
	val existsT2 = ((exists (1,[1,2,3])) = true)
	val existsT3 = ((exists ([1],[[1]])) = true)
	val existsT4 = ((exists ([1],[[3],[5]])) = false)
	val existsT5 = ((exists ("c",["b","c","z"])) = true)
	val existsT6 = ((exists (4,[3,5,6,7,4])) = true) 
in
	print ("\nProblem 1-A\n\nexists:-------------------- \n" ^
		" test1: " ^ Bool.toString(existsT1) ^ "\n" ^
		" test2: " ^ Bool.toString(existsT2) ^ "\n" ^
		" test3: " ^ Bool.toString(existsT3) ^ "\n" ^
		" test4: " ^ Bool.toString(existsT4) ^ "\n" ^
		" test5: " ^ Bool.toString(existsT5) ^ "\n" ^
		" test6: " ^ Bool.toString(existsT6) ^ "\n")
end 

val _ = existsTest();

(*Part B*)
(*The type is not ('a*'a list) -> bool because the 'a*' is an alpha
type meaning that it can be representative of any variable type. 
In this function we are comparing variables so we want to use the comparable
type ''a*'' instead.*)

(*Part C*)

fun countInListTest () =
let
	fun countInList [] x = 0 
		| countInList (y::rest) x = 
			if (x=y) then 1 + (countInList rest x)
			else countInList rest x;

	val countInListT1 = ((countInList ["3","5","5","-","4","5","1"] "5") = 3)
	val countInListT2 = ((countInList [] "5") = 0)
	val countInListT3 = ((countInList [true, false, false, false, true, true, true] true) = 4)
	val countInListT4 = ((countInList [[],[1,2],[3,2],[5,6,7],[8],[]] []) = 2)
	val countInListT5 = ((countInList [[1,2],[3,2],[5,6,7],[8],[1,2]] [1,2]) = 2)	
in
	print ("\nProblem 1-C\n\ncountInList:-------------------- \n" ^
		" test1: " ^ Bool.toString(countInListT1) ^ "\n" ^
		" test2: " ^ Bool.toString(countInListT2) ^ "\n" ^
		" test3: " ^ Bool.toString(countInListT3) ^ "\n" ^
		" test4: " ^ Bool.toString(countInListT4) ^ "\n" ^
		" test5: " ^ Bool.toString(countInListT5) ^ "\n")
end

val _ = countInListTest();


(*--------Problem 2--------*)

fun countInListTuple ([],x) = 0
	| countInListTuple(y::rest, x) = 
		if y=x then 1+countInListTuple(rest,x) 
		else countInListTuple(rest,x);

fun chooseMaximum(x,y) = if x>y then x else y;

fun removeFromList([],x) = []
	| removeFromList(y::rest,x) = 
		if y=x then removeFromList(rest,x) 
		else y::removeFromList(rest,x);

fun repeatElement(x,0) = []
	| repeatElement(x,n) = x::repeatElement(x,n-1);

	
fun listDiffTest () =
let 
	fun listDiff([],l) = []
		| listDiff(y::rest,l) = repeatElement(y,chooseMaximum(countInListTuple(y::rest,y)-countInListTuple(l,y),0))
		@ listDiff(removeFromList(y::rest,y),l);

	val listDiffT1 = ((listDiff (["a","b","c"],["b"])) = ["a", "c"])
	val listDiffT2 = ((listDiff ([1,2,3],[1,1,2])) = [3])
	val listDiffT3 = ((listDiff ([1,2,2,3,3,3],[1,1,2,3])) = [2,3,3])
	val listDiffT4 = ((listDiff ([[2,3],[1,2],[2,3]],[[1],[2,3]])) = [[2,3],[1,2]])
	val listDiffT5 = ((listDiff ([1,2,3],[])) = [1,2,3])
	val listDiffT6 = ((listDiff ([1,2,3,4,5],[1,2,3,4,5])) = [])
in 
	print ("\nProblem 2\n\nlistDiff:-------------------- \n" ^
		" test1: " ^ Bool.toString(listDiffT1) ^ "\n" ^
		" test2: " ^ Bool.toString(listDiffT2) ^ "\n" ^
		" test3: " ^ Bool.toString(listDiffT3) ^ "\n" ^
		" test4: " ^ Bool.toString(listDiffT4) ^ "\n" ^
		" test5: " ^ Bool.toString(listDiffT5) ^ "\n" ^
		" test6: " ^ Bool.toString(listDiffT6) ^ "\n")
end

val _ = listDiffTest ();
	
	
(*--------Problem 3--------*)

fun firstNTest () =
let	
	fun firstN [] n = []
		| firstN (x::rest) 0 = []
		| firstN (x::rest) n = 
			if length (x::rest) < n then (x::rest)
			else x::(firstN rest (n-1));

	val firstNT1 = ((firstN [1,2,3,4,5,6,7] 4) = [1,2,3,4])
	val firstNT2 = ((firstN [1,2,3,4,5,6,7] 10) = [1,2,3,4,5,6,7])
	val firstNT3 = ((firstN [[1,2,3],[4,5],[6],[],[7,8],[]] 4) = [[1,2,3],[4,5],[6],[]])
	val firstNT4 = ((firstN [] 5) = [])
	val firstNT5 = ((firstN [1] 20) = [1])
in
	print ("\nProblem 3\n\nfirstN:-------------------- \n" ^
		" test1: " ^ Bool.toString(firstNT1) ^ "\n" ^
		" test2: " ^ Bool.toString(firstNT2) ^ "\n" ^
		" test3: " ^ Bool.toString(firstNT3) ^ "\n" ^
		" test4: " ^ Bool.toString(firstNT4) ^ "\n" ^
		" test5: " ^ Bool.toString(firstNT5) ^ "\n")
end

val _ = firstNTest ();


(*--------Problem 4--------*)

fun busFinderTest () =
let
	fun busFinder x [] = []
		| busFinder x ((bus,(y::rest))::rest2) =
		if exists (x,(y::rest)) then bus::busFinder x rest2
		else busFinder x rest2;

	val buses =
		[("Lentil",["Chinook", "Orchard", "Valley", "Emerald","Providence", "Stadium",
		"Main", "Arbor", "Sunnyside", "Fountain", "Crestview", "Wheatland", "Walmart",
		"Bishop", "Derby", "Dilke"]),
		("Wheat",["Chinook", "Orchard", "Valley", "Maple","Aspen", "TerreView", "Clay",
		"Dismores", "Martin", "Bishop", "Walmart", "PorchLight", "Campus"]),
		("Silver",["TransferStation", "PorchLight", "Stadium", "Bishop","Walmart",
		"Shopco", "RockeyWay"]),
		("Blue",["TransferStation", "State", "Larry", "TerreView","Grand", "TacoBell",
		"Chinook", "Library"]),
		("Gray",["TransferStation", "Wawawai", "Main", "Sunnyside","Crestview",
		"CityHall", "Stadium", "Colorado"])]

	val busFinderT1 = ((busFinder "Walmart" buses) = ["Lentil","Wheat","Silver"])
	val busFinderT2 = ((busFinder "Shopco" buses) = ["Silver"])
	val busFinderT3 = ((busFinder "Main" buses) = ["Lentil","Gray"])
	val busFinderT4 = ((busFinder "Beasley" buses) = [])
	val busFinderT5 = ((busFinder "Stadium" buses) = ["Lentil","Silver","Gray"])
	val busFinderT6 = ((busFinder "Lentil" buses) = [])
in
	print ("\nProblem 4-A\n\nbusFinder:-------------------- \n" ^
		" test1: " ^ Bool.toString(busFinderT1) ^ "\n" ^
		" test2: " ^ Bool.toString(busFinderT2) ^ "\n" ^
		" test3: " ^ Bool.toString(busFinderT3) ^ "\n" ^
		" test4: " ^ Bool.toString(busFinderT4) ^ "\n" ^
		" test5: " ^ Bool.toString(busFinderT5) ^ "\n" ^
		" test6: " ^ Bool.toString(busFinderT6) ^ "\n")
end

val _ = busFinderTest ();

(*Part B*)
(*The type is ''a -> ('b * ''a list) list -> 'b list and not 
''a -> ('a * ''a list) list -> 'a list because in the function we do not 
compare the element of the tuple representing the bus name to the elements 
representing the stop names so the compiler shows different types for 
these elements as they are not comparable.*)


(*--------Problem 5--------*)

fun addResistors [] = 0.0
	| addResistors (x::rest) = ((1.0 / x) + addResistors (rest));

fun parallelResistorsTest () = 
let

	fun parallelResistors (x::rest) = 1.0 / addResistors (x::rest);

	val parallelResistorsT1 = Real.==((parallelResistors [10.0, 10.0, 10.0, 10.0]), 2.5)
	val parallelResistorsT2 = Real.==((parallelResistors [8.0, 16.0, 4.0, 16.0]), 2.0)
	val parallelResistorsT3 = Real.==((parallelResistors [5.0, 10.0, 2.0]), 1.25)
	val parallelResistorsT4 = Real.==((parallelResistors [5.0, 5.0, 10.0, 2.0]), 1.0)
	val parallelResistorsT5 = Real.==((parallelResistors [1.0]), 1.0)
in
	print ("\nProblem 5\n\nparallelResistors:-------------------- \n" ^
		" test1: " ^ Bool.toString(parallelResistorsT1) ^ "\n" ^
		" test2: " ^ Bool.toString(parallelResistorsT2) ^ "\n" ^
		" test3: " ^ Bool.toString(parallelResistorsT3) ^ "\n" ^
		" test4: " ^ Bool.toString(parallelResistorsT4) ^ "\n" ^
		" test5: " ^ Bool.toString(parallelResistorsT5) ^ "\n")
end

val _ = parallelResistorsTest ();

(*--------Problem 6--------*)

fun pairHelper n buff [] = [rev(buff)]
  | pairHelper n buff (x::rest) = 
		if length(buff) = n then rev(buff)::(pairHelper n (x::[]) rest)
		else pairHelper n (x::buff) rest;
		
fun pairHelper2 n buff [] = [rev(buff)]
  | pairHelper2 n buff (x::rest) = 
		if length(buff) = n then buff::(pairHelper2 n (x::[]) rest)
		else pairHelper2 n (x::buff) rest;
		
fun reverse buff [] = buff
  | reverse buff (x::rest) = reverse (x::buff) rest;

fun pairNleft (x, []) = []
  | pairNleft (x, List) = 
						let
							val z = reverse [] List
						in 
							rev(pairHelper2 x [] z)
						end;

fun pairNright (x, []) = []
  | pairNright (x, List) = pairHelper x [] List;
  

fun pairNTest () = 
let
	val pairNrightT1 = ((pairNright (3,[1, 2, 3, 4, 5]) = [[1, 2, 3], [4, 5]]))
	val pairNrightT2 = ((pairNright (2,[1, 2, 3, 4, 5]) = [[1, 2], [3, 4], [5]]))
	val pairNrightT3 = ((pairNright (3,[]) = [[]]))
	val pairNleftT1 = ((pairNleft (2,[1, 2, 3, 4, 5]) = [[1], [2, 3], [4, 5]]))
	val pairNleftT2 = ((pairNleft (3,[1, 2, 3, 4, 5]) = [[1, 2], [3, 4, 5]]))
in
	print ("\nProblem 6\n\npairNTest:-------------------- \n" ^
		" test1: " ^ Bool.toString(pairNrightT1) ^ "\n" ^
		" test2: " ^ Bool.toString(pairNrightT2) ^ "\n" ^
		" test3: " ^ Bool.toString(pairNrightT3) ^ "\n" ^
		" test4: " ^ Bool.toString(pairNleftT1) ^ "\n" ^
		" test5: " ^ Bool.toString(pairNleftT2) ^ "\n")
end

val _ = pairNTest ();






