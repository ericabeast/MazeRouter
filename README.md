# Maze Router
Goal:
Given a gridded routing region, and find the routes for all the two-terminal pairs.

## Run the code
```hash
1. make
2. ./run [input_file.txt][output_file_name.txt]
```


## Inputs
Your input file should have the following inputs:

```bash
1. the size of the maze
2. how many blocks and the four coordinates of the blocks.
3. how many nets and the source and the target coordinate. (X,Y)
```

## Outputs

```bash
1. total grid usage
2. grid start point to grid end point
```

## Example

```bash
#input
.row 12         // Routing region
.col 12

.blk 3          // 3 blockages
2 3 3 8         // Left_down_X Left_down_Y Right_up_X Right_up_Y
5 3 10 8
0 10 10 11

.net 2          // 2 nets
Net1 3 9 11 11  // Source_X Source_Y Target_X Target_Y
Net2 6 2 6 9



#output
Net1
begin
29
3 9 1 9
1 9 1 1
1 1 11 1
11 1 11 1
end
Net2
begin
10
6 2 4 2
4 2 4 9
4 9 6 9
end
```

<!-- ## Contributing

Pull requests are welcome. For major changes, please open an issue first
to discuss what you would like to change.

Please make sure to update tests as appropriate. -->

<!-- ## License

-->