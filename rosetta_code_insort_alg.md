function insertionSort(array A)
	for i from 1 to length[A] - 1 do
		value := A[i]
		j := i - 1
		while j >= 0 and A[j] > value do
			A[j + 1] := A[j]
			j := j - 1;
		done
		A[j + 1] = value
	done
