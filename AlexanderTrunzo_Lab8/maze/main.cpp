//----------------------------------------------------------------------------
// by Christopher Rasmussen, cer@cis.udel.edu
// created: October, 2014
// v. 1.00
//----------------------------------------------------------------------------

#include "maze.hh"
#include "unionfind.hh"

//----------------------------------------------------------------------------
//----------------------------------------------------------------------------

// global variables

Maze *M = NULL;
UnionFind *U = NULL;

//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
//takes size of unionset, iterates through and finds max height
// OPTION 1

// knock down random walls one at a time until they're all gone.
// ATM, this does nothing to associated union-find data structure

void knock_down_all_walls()
{
  int dir, i, j;
  
  while (M->pick_random_wall(dir, i, j)) {

    M->print_wall_location(dir, i, j);
    M->knock_down_wall(dir, i, j);

    // update union-find data structure U

    // east
    
    if (dir == 0){
	if(U->find(M->rowcol_to_UF_index(i,j)) == U->find(M->rowcol_to_UF_index(i, j+1))){

}

	else{
    	U->union_sets_by_size(U->find(M->rowcol_to_UF_index(i,j)), (M->rowcol_to_UF_index(i, j+1)));
}
}
    //south
    else if (dir ==1){

	if(U->find(M->rowcol_to_UF_index(i,j)) == U->find(M->rowcol_to_UF_index(i+1, j))){}
	else{
    	U->union_sets_by_size(U->find(M->rowcol_to_UF_index(i,j)), (M->rowcol_to_UF_index(i+1, j)));
}
}

    

    M->print();
    U->print_horizontal();
    //U->print_vertical();
  }
}

//----------------------------------------------------------------------------

// OPTION 2

// knock down random walls one at a time until START and FINISH are connected.
// nothing else is considered

void knock_down_til_solvable()
{
  int dir, i, j;
  while (U->find(M->num_rows * M->num_cols -1) != U->find(M->rowcol_to_UF_index(M->start_row, M->start_col))){

  

    M->print_wall_location(dir, i, j);
    M->knock_down_wall(dir, i, j);

    // update union-find data structure U

    // east
    
    if (dir == 0){
	if(U->find(M->rowcol_to_UF_index(i,j)) == U->find(M->rowcol_to_UF_index(i, j+1))){

}

	else{
    	U->union_sets_by_size(U->find(M->rowcol_to_UF_index(i,j)), (M->rowcol_to_UF_index(i, j+1)));
}
}
    //south
    else if (dir ==1){

	if(U->find(M->rowcol_to_UF_index(i,j)) == U->find(M->rowcol_to_UF_index(i+1, j))){}
	else{
    	U->union_sets_by_size(U->find(M->rowcol_to_UF_index(i,j)), (M->rowcol_to_UF_index(i+1, j)));
}
}

    

    M->print();
    U->print_horizontal();
    M->pick_random_wall(dir, i, j);
} 
}

//----------------------------------------------------------------------------

// OPTION 3

// knock down random walls one at a time until START and FINISH are connected.
// now we only knock down a wall if the cells on either side of it are NOT already
// connected

void knock_down_til_solvable_better()
{

  int dir, i, j;
  while (U->find(M->num_rows * M->num_cols -1) != U->find(M->rowcol_to_UF_index(M->start_row, M->start_col))){

   

    M->print_wall_location(dir, i, j);
   
    // update union-find data structure U

    // east
    
    if (dir == 0){
	if(U->find(M->rowcol_to_UF_index(i,j)) == U->find(M->rowcol_to_UF_index(i, j+1))){

	}	

	else{

    	M->knock_down_wall(dir, i, j);
    	U->union_sets_by_size(U->find(M->rowcol_to_UF_index(i,j)), (M->rowcol_to_UF_index(i, j+1)));
}
}
    //south
    else if (dir ==1){

	if(U->find(M->rowcol_to_UF_index(i,j)) == U->find(M->rowcol_to_UF_index(i+1, j))){


	}
	else{

    	M->knock_down_wall(dir, i, j);
    	U->union_sets_by_size(U->find(M->rowcol_to_UF_index(i,j)), (M->rowcol_to_UF_index(i+1, j)));
}
}
 

    

    M->print();
    U->print_horizontal();
    M->pick_random_wall(dir, i, j);
} 
}

//----------------------------------------------------------------------------

// OPTION 5
//option 4 using dumb union


void knock_down_til_all_connected()
{
  int rows = M->num_rows-1;
  int cols = M->num_cols-1;

  
//solvable
  int dir, i, j;
  while (U->find(M->num_rows * M->num_cols -1) != U->find(M->rowcol_to_UF_index(M->start_row, M->start_col))){

   

    M->print_wall_location(dir, i, j);

    // update union-find data structure U

    // east
    
    if (dir == 0){
	if(U->find(M->rowcol_to_UF_index(i,j)) == U->find(M->rowcol_to_UF_index(i, j+1))){

	}	

	else{

    	M->knock_down_wall(dir, i, j);
    	U->union_sets(U->find(M->rowcol_to_UF_index(i,j)), (M->rowcol_to_UF_index(i, j+1)));
}
}
    //south
    else if (dir ==1){

	if(U->find(M->rowcol_to_UF_index(i,j)) == U->find(M->rowcol_to_UF_index(i+1, j))){


	}
	else{

    	M->knock_down_wall(dir, i, j);
    	U->union_sets(U->find(M->rowcol_to_UF_index(i,j)), (M->rowcol_to_UF_index(i+1, j)));
}
}
 

    

    M->print();
    U->print_horizontal();
    M->pick_random_wall(dir, i, j);
} 


//connected
  for(int r =0; r < rows; r++){
	for(int c=0; c < cols; c++){
		if (U->find(M->rowcol_to_UF_index(r, c)) != M->rowcol_to_UF_index(M->start_row, M->start_col)){
			//break a wall
			if(r == M->num_rows){
				M->knock_down_wall(0, r, c);
    				U->union_sets(U->find(M->rowcol_to_UF_index(r,c)), (M->rowcol_to_UF_index(r, c+1)));
				M->print();
    				U->print_horizontal();
			}
			else if(c == M->num_cols){
				M->knock_down_wall(1, r, c);
				U->union_sets(U->find(M->rowcol_to_UF_index(r,c)), (M->rowcol_to_UF_index(r+1, c)));
				M->print();
    				U->print_horizontal();
			}
			else{
				if(U->find(M->rowcol_to_UF_index(r,c)) == U->find(M->rowcol_to_UF_index(r, c+1))){

				}		

				else{

					M->knock_down_wall(0, r, c);
					U->union_sets(U->find(M->rowcol_to_UF_index(r,c)), (M->rowcol_to_UF_index(r, c+1)));
    					M->print();
    					U->print_horizontal();

			}
				
				if(U->find(M->rowcol_to_UF_index(r,c)) == U->find(M->rowcol_to_UF_index(r+1, c))){


				}
				else{

 			   	M->knock_down_wall(1, r, c);
    				U->union_sets(U->find(M->rowcol_to_UF_index(r,c)), (M->rowcol_to_UF_index(r+1, c)));
    				M->print();
    				U->print_horizontal();
}
	
	}}else{
}
  }
}
}
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
//Option 4
// same as option 3, but we only stop on the condition that the maze is solvable
// AND that every cell in it is connected to every other cell.  note that this 
// does not mean all the walls are down

void smart_knock_down_til_all_connected()
{
  int rows = M->num_rows-1;
  int cols = M->num_cols-1;

  
//solvable
  int dir, i, j;
  while (U->find(M->num_rows * M->num_cols -1) != U->find(M->rowcol_to_UF_index(M->start_row, M->start_col))){

   

    M->print_wall_location(dir, i, j);

    // update union-find data structure U

    // east
    
    if (dir == 0){
	if(U->find(M->rowcol_to_UF_index(i,j)) == U->find(M->rowcol_to_UF_index(i, j+1))){

	}	

	else{

    	M->knock_down_wall(dir, i, j);
    	U->union_sets_by_size(U->find(M->rowcol_to_UF_index(i,j)), (M->rowcol_to_UF_index(i, j+1)));
}
}
    //south
    else if (dir ==1){

	if(U->find(M->rowcol_to_UF_index(i,j)) == U->find(M->rowcol_to_UF_index(i+1, j))){


	}
	else{

    	M->knock_down_wall(dir, i, j);
    	U->union_sets_by_size(U->find(M->rowcol_to_UF_index(i,j)), (M->rowcol_to_UF_index(i+1, j)));
}
}
 

    

    M->print();
    U->print_horizontal();
    M->pick_random_wall(dir, i, j);
} 


//connected
  for(int r =0; r < rows; r++){
	for(int c=0; c < cols; c++){
		if (U->find(M->rowcol_to_UF_index(r, c)) != M->rowcol_to_UF_index(M->start_row, M->start_col)){
			//break a wall
			if(r == M->num_rows){
				M->knock_down_wall(0, r, c);
    				U->union_sets_by_size(U->find(M->rowcol_to_UF_index(r,c)), (M->rowcol_to_UF_index(r, c+1)));
				M->print();
    				U->print_horizontal();
			}
			else if(c == M->num_cols){
				M->knock_down_wall(1, r, c);
				U->union_sets_by_size(U->find(M->rowcol_to_UF_index(r,c)), (M->rowcol_to_UF_index(r+1, c)));
				M->print();
    				U->print_horizontal();
			}
			else{
				if(U->find(M->rowcol_to_UF_index(r,c)) == U->find(M->rowcol_to_UF_index(r, c+1))){

				}		

				else{

					M->knock_down_wall(0, r, c);
					U->union_sets_by_size(U->find(M->rowcol_to_UF_index(r,c)), (M->rowcol_to_UF_index(r, c+1)));
    					M->print();
    					U->print_horizontal();

			}
				
				if(U->find(M->rowcol_to_UF_index(r,c)) == U->find(M->rowcol_to_UF_index(r+1, c))){


				}
				else{

 			   	M->knock_down_wall(1, r, c);
    				U->union_sets_by_size(U->find(M->rowcol_to_UF_index(r,c)), (M->rowcol_to_UF_index(r+1, c)));
    				M->print();
    				U->print_horizontal();
}
	
	}}else{
}
  }
}
}
//---------------------------------------------------------------------------
//--------------------------------------------------------------------------
//Option 6
//Option 4 with no prints and height algorithm
void smart_height()
{
  int rows = M->num_rows-1;
  int cols = M->num_cols-1;
  int size = M->num_cols * M->num_rows -1;
  int height = 0; 
//solvable
  int dir, i, j;
  while (U->find(M->num_rows * M->num_cols -1) != U->find(M->rowcol_to_UF_index(M->start_row, M->start_col))){

   

    //M->print_wall_location(dir, i, j);
   

    // update union-find data structure U

    // east
    
    if (dir == 0){
	if(U->find(M->rowcol_to_UF_index(i,j)) == U->find(M->rowcol_to_UF_index(i, j+1))){

	}	

	else{

    	M->knock_down_wall(dir, i, j);
    	U->union_sets_by_size(U->find(M->rowcol_to_UF_index(i,j)), (M->rowcol_to_UF_index(i, j+1)));
}
}
    //south
    else if (dir ==1){

	if(U->find(M->rowcol_to_UF_index(i,j)) == U->find(M->rowcol_to_UF_index(i+1, j))){


	}
	else{

    	M->knock_down_wall(dir, i, j);
    	U->union_sets_by_size(U->find(M->rowcol_to_UF_index(i,j)), (M->rowcol_to_UF_index(i+1, j)));
}
}
 

    

    //M->print();
    //U->print_horizontal();
    M->pick_random_wall(dir, i, j);
} 


//connected
  for(int r =0; r < rows; r++){
	for(int c=0; c < cols; c++){
		if (U->find(M->rowcol_to_UF_index(r, c)) != M->rowcol_to_UF_index(M->start_row, M->start_col)){
			//break a wall
			if(r == M->num_rows){
				M->knock_down_wall(0, r, c);
    				U->union_sets_by_size(U->find(M->rowcol_to_UF_index(r,c)), (M->rowcol_to_UF_index(r, c+1)));
				//M->print();
    				//U->print_horizontal();
			}
			else if(c == M->num_cols){
				M->knock_down_wall(1, r, c);
				U->union_sets_by_size(U->find(M->rowcol_to_UF_index(r,c)), (M->rowcol_to_UF_index(r+1, c)));
				//M->print();
    				//U->print_horizontal();
			}
			else{
				if(U->find(M->rowcol_to_UF_index(r,c)) == U->find(M->rowcol_to_UF_index(r, c+1))){

				}		

				else{

					M->knock_down_wall(0, r, c);
					U->union_sets_by_size(U->find(M->rowcol_to_UF_index(r,c)), (M->rowcol_to_UF_index(r, c+1)));
    					//M->print();
    					//U->print_horizontal();

			}
				
				if(U->find(M->rowcol_to_UF_index(r,c)) == U->find(M->rowcol_to_UF_index(r+1, c))){


				}
				else{

 			   	M->knock_down_wall(1, r, c);
    				U->union_sets_by_size(U->find(M->rowcol_to_UF_index(r,c)), (M->rowcol_to_UF_index(r+1, c)));
    				//M->print();
    				//U->print_horizontal();
}
	
	}}else{
}
  }
}
	for(int z=0; z <= size; z++){
		if(U->height(z) > height){
			height = U->height(z);
		}
	}
	cout<<"Height: "<<height<<"\n";
	
}
//-------------------------------------------------------------------------
//---------------------------------------------------------------------------
//option 7
//option 5 with no prints and height algorithm
void dumb_height()
{
  int rows = M->num_rows-1;
  int cols = M->num_cols-1;
  int size = M->num_cols * M->num_rows -1;
  int height = 0; 
//solvable
  int dir, i, j;
  while (U->find(M->num_rows * M->num_cols -1) != U->find(M->rowcol_to_UF_index(M->start_row, M->start_col))){

   

    //M->print_wall_location(dir, i, j);

    // update union-find data structure U

    // east
    
    if (dir == 0){
	if(U->find(M->rowcol_to_UF_index(i,j)) == U->find(M->rowcol_to_UF_index(i, j+1))){

	}	

	else{

    	M->knock_down_wall(dir, i, j);
    	U->union_sets(U->find(M->rowcol_to_UF_index(i,j)), (M->rowcol_to_UF_index(i, j+1)));
}
}
    //south
    else if (dir ==1){

	if(U->find(M->rowcol_to_UF_index(i,j)) == U->find(M->rowcol_to_UF_index(i+1, j))){


	}
	else{

    	M->knock_down_wall(dir, i, j);
    	U->union_sets(U->find(M->rowcol_to_UF_index(i,j)), (M->rowcol_to_UF_index(i+1, j)));
}
}
 

    

    //M->print();
    //U->print_horizontal();
    M->pick_random_wall(dir, i, j);
} 


//connected
  for(int r =0; r < rows; r++){
	for(int c=0; c < cols; c++){
		if (U->find(M->rowcol_to_UF_index(r, c)) != M->rowcol_to_UF_index(M->start_row, M->start_col)){
			//break a wall
			if(r == M->num_rows){
				M->knock_down_wall(0, r, c);
    				U->union_sets(U->find(M->rowcol_to_UF_index(r,c)), (M->rowcol_to_UF_index(r, c+1)));
				//M->print();
    				//U->print_horizontal();
			}
			else if(c == M->num_cols){
				M->knock_down_wall(1, r, c);
				U->union_sets(U->find(M->rowcol_to_UF_index(r,c)), (M->rowcol_to_UF_index(r+1, c)));
				//M->print();
    				//U->print_horizontal();
			}
			else{
				if(U->find(M->rowcol_to_UF_index(r,c)) == U->find(M->rowcol_to_UF_index(r, c+1))){

				}		

				else{

					M->knock_down_wall(0, r, c);
					U->union_sets(U->find(M->rowcol_to_UF_index(r,c)), (M->rowcol_to_UF_index(r, c+1)));
    					//M->print();
    					//U->print_horizontal();

			}
				
				if(U->find(M->rowcol_to_UF_index(r,c)) == U->find(M->rowcol_to_UF_index(r+1, c))){


				}
				else{

 			   	M->knock_down_wall(1, r, c);
    				U->union_sets(U->find(M->rowcol_to_UF_index(r,c)), (M->rowcol_to_UF_index(r+1, c)));
    				//M->print();
    				//U->print_horizontal();
}
	
	}}else{
}
  }
}

	for(int z=0; z <= size; z++){
		if(U->height(z) > height){
			height = U->height(z);
		}
	
	}
	cout<<"Height: "<<height<<"\n";
}

//---------------------------------------------------------------------------
//----------------------------------------------------------------------------
int main(int argc, char** argv)
{
  // initialize maze

  // 2 arguments: rows and cols

  if (argc == 3) {
    M = new Maze(atoi(argv[1]), atoi(argv[2]));
  }

  // no arguments: assume 5 x 5

  else if (argc < 2) {
    cout << "Creating default 5 x 5 maze" << endl;
    M = new Maze(5, 5);
  }

  // 1 argument: same number of rows as cols

  else
    M = new Maze(atoi(argv[1]), atoi(argv[1]));
  
  // initialize corresponding union-find data structure

  U = new UnionFind(M->num_rows * M->num_cols);

  if (!M || !U) {
    cout << "Must properly initialize maze and union-find data structure before continuing" << endl;
    exit(1);
  }

  // set start and finish locations 

  M->set_start_and_finish(0, 0, M->num_rows - 1, M->num_cols - 1);

  // show original maze
  
  M->print();
  U->print_horizontal();
  
  // get user input on what to do

  cout << "Please choose one of the following:\n1 Knock down walls randomly until all gone\n2 Knock down walls until start and finish are connected\n3 Same as 2, but make sure cells on each side of wall are not already connected\n4 Same as 3, but keep going until ALL cells are connected to each other\n5 Same as 4 but uses dumb union\n6 Same as 4 but no prints and has height algo\n7 same as 5 but no prints and has height algo\nAnything else to exit" << endl;

  int input_val;

  cin >> input_val;

  switch (input_val) 
    {
      
    case 0: 
      exit(1);
      
    case 1: 
      knock_down_all_walls();
      exit(1);
      
    case 2:
      knock_down_til_solvable();
      exit(1);

    case 3:
      knock_down_til_solvable_better();
      exit(1);

    case 4:
      smart_knock_down_til_all_connected();
      exit(1);
    case 5:
      knock_down_til_all_connected();
      exit(1);
    case 6:
      smart_height();
      exit(1);
    case 7:
      dumb_height();
      exit(1);
    }

  return 1;
}

//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
