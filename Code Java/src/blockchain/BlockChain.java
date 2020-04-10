package blockchain;

import utils.*;
import java.util.ArrayList;

public class BlockChain {
	private int difficulty;
	private int nbBlocks;
	private ArrayList<Blocks> blocksList = new ArrayList<>();
	
	public BlockChain(int difficulty, int nbBlocks) {
        this.difficulty = difficulty;
        this.nbBlocks = nbBlocks;;
        this.blocksList.add(this.genesisGenerator());
    }
		
	public ArrayList<Blocks> getBlocksList() {
		return blocksList;
	}

	public Blocks genesisGenerator() {
		Date timestamp = new Date();
		Blocks genesis = new Blocks(0, timestamp, "0", "Genesis");
		return genesis;
	}
	
	public Blocks addBlock(Blocks block) {
        if (block != null ){
            block.blockMining(difficulty);
            blocksList.add(block);
        }
        return block;
    }

	public void printBlockList() {
		for (int i = 0; i < blocksList.size(); i++) {
		      blocksList.get(i).printBlock();
		}
	}
}
