from heapq import heappush, heappop

flights = []

N = int(input())

for _ in range(N):
    scheduled, runaway_time = map(int, input().split())
    flights.append((scheduled, runaway_time))

flights.sort(reverse=True)

pq = []
time_delay = 0
current_time = 0

while flights or pq:
    while flights and flights[-1][0] <= current_time:
        heappush(pq, flights.pop()[::-1])
    if pq:
        current_task = heappop(pq)
        current_time += current_task[0]
        time_delay += current_time - current_task[1]
    else:
        heappush(pq, flights.pop()[::-1])
        current_time = pq[0][1]

print(time_delay // N)
