import java.io.*;

//Michael Rokas
//May 16th 2019

class p096 {
  public static void main(String[] args) {
    try {
      File file = new File("inputs.txt"); 
      BufferedReader br = new BufferedReader(new FileReader(file)); 
      
      int index = 0;
      int sum = 0;

      byte[][] board = new byte[9][9];

      String str;
      while ((str = br.readLine()) != null) {
        if(str.charAt(0) == 'G')
          continue;

        fillRow(board[index], str);

        if(index == 8) {
          attemptSolve(board);
          sum += board[0][0]*100 + board[0][1]*10 + board[0][2];
        }
        index = (index+1) % 9;
      } 
      System.out.println("Sum: " + sum);  
    } catch(IOException e){}
  }

  private static void fillRow(byte[] row, String str) {
    for(int i = 0; i < 9; i++)
      row[i] = (byte)(str.charAt(i) - 48);
  }

  private static boolean attemptSolve(byte[][] board) {
    for(int i = 0; i < 9; i++) {
      for(int j = 0; j < 9; j++) {
        if(board[i][j] == 0) {
          for(byte k = 1; k <= 9; k++) {
            if(canPut(i,j,k,board)) {
              board[i][j] = k;
              if(attemptSolve(board))
                return true;
              else
                board[i][j] = 0;
            }
          }
          return false;
        }
      }
    }
    return true;
  }

  public static boolean canPut(int row, int col, byte k, byte[][] board) {
    for(int i = 0; i < 9; i++) {
      if(board[row][i] == k || board[i][col] == k)
        return false;
    }

    int rowStart = (row/3)*3;
    int colStart = (col/3)*3;

    for(int i = rowStart; i < rowStart+3; i++){
      for(int j = colStart; j < colStart+3; j++)
        if(board[i][j] == k)
          return false;
    }

    return true;
  }
}