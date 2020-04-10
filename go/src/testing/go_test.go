package main

import "testing"

func TestSumSingle(t *testing.T) {
	total := Sum(5, 5)
	if total != 10 {
		t.Errorf("5 + 5 = %d, expected 10", total)
	}
}

func TestSumTable(t *testing.T) {
	tables := []struct {
		x int
		y int
		n int
	}{
		{1, 1, 2},
		{1, 2, 3},
		{2, 2, 4},
		{5, 2, 7},
	}

	for _, table := range tables {
		total := Sum(table.x, table.y)
		if total != table.n {
			t.Errorf("Sum of (%d+%d) was incorrect, got: %d, want: %d.", table.x, table.y, total, table.n)
		}
	}
}
