
import Foundation

guard CommandLine.argc == 3 else {
    print("Usage gcd -[s|p] ITERATIONS")
    exit(1)
}

guard let iterations = Int(CommandLine.arguments[2]) else {
    print("Usage gcd -[s|p] ITERATIONS")
    exit(1)
}

func sumForIndex(index: Int) -> Int {
    var sum = 0
    for i in 0...index {
        sum += i
    }
    return sum
}

var sums: [Int] = []
sums.reserveCapacity(iterations + 1)

let start = DispatchTime.now()

if CommandLine.arguments[1] == "-s" {
    for i in 0...iterations {
        sums.append(sumForIndex(index: i))
    }
} else if CommandLine.arguments[1] == "-p" {
    DispatchQueue.concurrentPerform(iterations: iterations, execute: { (index) in
        sums.append(sumForIndex(index: index))
    })
    
} else {
    print("Usage gcd -[s|p] ITERATIONS")
    exit(1)
}

let end = DispatchTime.now()

print(end.uptimeNanoseconds - start.uptimeNanoseconds) / 1_000_000)


