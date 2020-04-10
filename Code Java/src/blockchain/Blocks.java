package blockchain;
import transactions.*;
import utils.*;
import java.util.ArrayList;

public class Blocks {
	private int index;
	private String timestamp;
	private String previousBlockHash;
	private int nbTransactions;
	private ArrayList<Transaction> transacList;
	private String Gdata;
	private String merkleHashRoot;
	private String currentBlockHash;
	private int nounce;
	
	//Genesis Constructor
	public Blocks(int index, Date timestamp, String previousBlockHash, String Gdata) {
		this.index = index;
		this.timestamp = timestamp.toString();
		this.previousBlockHash = previousBlockHash;
		this.Gdata = Gdata;
		nounce = 0;
		this.currentBlockHash = genesisHashGenerator(this);
	}

	//Other Blocks Constructor
	public Blocks(int index, String previousBlockHash,Date timestamp, ArrayList<Transaction> transacList) {
        this.index = index;
        this.timestamp = timestamp.toString();
        this.previousBlockHash = previousBlockHash;
        this.nbTransactions = index + 1;
        this.transacList = transacList;
        nounce = 0;
        this.currentBlockHash = hashGenerator(this);
    }
	
	public String getCurrentBlockHash() {
		return currentBlockHash;
	}
	
	public int getIndex() {
		return index;
	}

	public String getTimestamp() {
		return timestamp;
	}

	public String getPreviousBlockHash() {
		return previousBlockHash;
	}

	public String stringForHashGen() {
        return index + timestamp + previousBlockHash + transacList + Integer.toString(nounce);
   }
	
	public String stringForGenesisHashGen() {
		return index + timestamp + previousBlockHash + Gdata + Integer.toString(nounce);
	}
	
	public static String hashGenerator(Blocks block) {
        if(block != null) {
            String str = block.stringForHashGen();
            return HashUtils.applySha256(str);
        }
        return null;
    }
	
	public static String genesisHashGenerator(Blocks block) {
        if(block != null) {
            String str = block.stringForGenesisHashGen();
            return HashUtils.applySha256(str);
        }
        return null;
    }
	
	public void printBlock() {
		System.out.println("Block n°" + this.index + " :");
		System.out.println("[");
		System.out.println("   Previous Block Hash = " + this.previousBlockHash);
		System.out.println("   Current Block Hash = " + this.currentBlockHash);
		System.out.println("   Timestamp = " + this.timestamp);
		if (this.index == 0){
			System.out.println("   Genesis Data = " + this.Gdata);
		}
		else if (this.transacList != null) {
			for (int i = 0; i < transacList.size(); i++) {
			System.out.println("   Transaction List = " + this.transacList.get(i));
			}
		}
		else {
			System.out.println("   Transaction List = null");
		}
		System.out.println("]\n");
	}
	
	
	public void blockMining(int difficulty) {
	    nounce = 0;
	    while(!getCurrentBlockHash().substring(0, difficulty).equals(HashUtils.difficultyZerosIncrmt(difficulty))) {
	        nounce++;
	        currentBlockHash = hashGenerator(this);
	    }
	}
}

