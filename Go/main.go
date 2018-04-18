package main

import (
	"os"
	"strconv"
	"sync"
	"time"
)

func sumForIndex(index int) int64 {
	var sum int64
	for i := 0; i < index; i++ {
		sum = sum + int64(i)
	}
	return sum
}

func computeSequencially(iterations int) {
	sums := make([]int64, iterations)
	for i := 0; i < iterations; i++ {
		sums[i] = sumForIndex(i)
	}
}

func computeConcurrently(iterations int) {
	sums := make([]int64, iterations)
	waitGroup := sync.WaitGroup{}
	waitGroup.Add(iterations)
	for i := 0; i < iterations; i++ {
		go func(i int) {
			sums[i] = sumForIndex(i)
			waitGroup.Done()
		}(i)
	}
	waitGroup.Wait()
}

func main() {

	argsWithoutProg := os.Args[1:]

	numberOfIterations, err := strconv.Atoi(argsWithoutProg[1])

	if err != nil {
		println("Usage: a.out -[s|p] iterations")
		return
	}

	begin := time.Now()

	if argsWithoutProg[0] == "-s" {
		computeSequencially(numberOfIterations)
	} else if argsWithoutProg[0] == "-p" {
		computeConcurrently(numberOfIterations)
	}

	timeElapsed := time.Since(begin)

	println("time elapsed:", timeElapsed/1000000, "ms")

}
