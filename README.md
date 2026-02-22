# Polygon Area Calculation and Optimal Grid Partition (C)

This project was developed for the Programming Laboratory I course.

The objective is to calculate the area of a polygon defined by coordinate points and to partition the region into optimally sized square grids in order to minimize total operational cost.

## Project Description

The project consists of two main phases:

### Phase 1 – Polygon Processing
- Read coordinate points from a web source
- Draw the polygon
- Calculate surface area
- Compute reserve value (Area × 10)

### Phase 2 – Optimal Grid Partition
- Divide the polygon into square regions (1x1, 2x2, 4x4, 8x8, 16x16)
- Apply adjacency constraints
- Minimize total cost:
  - Drilling cost
  - Platform cost
- Calculate profit

## Technologies

- C Programming Language
- Computational Geometry
- Grid-based optimization

## Output

The program:
- Draws the polygon
- Displays calculated area
- Visualizes grid partition
- Outputs total cost and profit
