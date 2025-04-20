fun filter _ nil = nil
  | filter f (x::xs) = if f x then x :: filter f xs else filter f xs;

fun quicksort cmp nil = nil
  | quicksort cmp (x::xs) =
      let
        val less = filter (fn y => cmp (y, x) = LESS) xs
        val greaterOrEqual = filter (fn y => cmp (y, x) <> LESS) xs
      in
        quicksort cmp less @ (x :: quicksort cmp greaterOrEqual)
      end;
