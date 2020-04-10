package main;
import blockchain.*;
import utils.Date;


public class tests {

	public static void main(String[] args) {
		
		System.out.println("Generating BlockChain with Genesis...\n");
		BlockChain testBlockchain = new BlockChain(1, 10);
		testBlockchain.printBlockList();
		
		System.out.println("Adding Block n°1...\n");
		Date timestampB1 = new Date();
		Blocks block1 = new Blocks(testBlockchain.getBlocksList().size(), testBlockchain.getBlocksList().get(testBlockchain.getBlocksList().size()-1).getCurrentBlockHash(), timestampB1, null);
		testBlockchain.addBlock(block1);
		testBlockchain.printBlockList();
	}

}
