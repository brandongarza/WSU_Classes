/**
 * Created by brand on 12/9/2018.
 */
public class Player {

    private int piecesCleared;
    private int playerScore;

    public Player(){
        piecesCleared = 0;
        playerScore = 0;
    }

    public int getCleared() { return this.piecesCleared; }
    public int getScore() { return this.playerScore; }
    public int setCleared(int cleared) { return this.piecesCleared = cleared; }
    public int setScore(int score) { return this.playerScore = score; }
}
