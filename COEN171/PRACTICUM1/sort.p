// Name: Logan Calder
// Date: 10/12/2024
// Title: Practicum 1 – 2.1: QuickSort (Pascal)

program sort(input, output);
    const high = 8;
    type numbers = array[1 .. high] of integer;
    var a : numbers;

    procedure readarray;
	var i : integer;
    begin
		for i := 1 to high do
			read(a[i])
		end;

    procedure writearray;
	var i : integer;
    begin
		for i := 1 to high do
			writeln(a[i]);
		end;

    procedure quicksort(var a : numbers; m, n : integer);
		type comparator = function (x, y : integer) : integer;
		var i : integer;

		function partition(var a : numbers; y, z : integer) : integer;
			var i, j, x : integer;

			procedure exchange(var a, b : integer);
			var t : integer;
			begin
			t := a;
			a := b;
			b := t
			end;

		begin
			x := a[y];
			i := y - 1;
			j := z + 1;

			while i < j do begin
				repeat
					j := j - 1
				until a[j] <= x;

				repeat
					i := i + 1
				until a[i] >= x;

				if i < j then
					exchange(a[i], a[j]);
			end;

			partition := j
		end;

	function compare(x, y: Integer): Integer;
		begin
		if x > y then
			compare := 1
		else if x = y then
			compare := 0
		else
			compare := -1;
		end;

    begin
		if compare(n, m) > 0 then begin
			i := partition(a, m, n);
			quicksort(a, m, i);
			quicksort(a, i + 1, n)
		end
    end;

begin
    readarray;
    quicksort(a, 1, high);
    writearray
end.
