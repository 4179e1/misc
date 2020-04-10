package main

import "testing"

func TestSum(t *testing.T) {
	type args struct {
		x int
		y int
	}
	tests := []struct {
		name string
		args args
		want int
	}{
		// TODO: Add test cases.
		{
			name: "test a",
			args: args{x: 1, y: 1},
			want: 2,
		},
		{
			"test b",
			args{2, 2},
			4,
		},
		{"test c", args{4, 4}, 8},
		{"test d", args{4, 4}, 7},
	}
	for _, tt := range tests {
		t.Run(tt.name, func(t *testing.T) {
			if got := Sum(tt.args.x, tt.args.y); got != tt.want {
				t.Errorf("Sum() = %v, want %v", got, tt.want)
			}
		})
	}
}
