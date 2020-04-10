package utils;

import java.util.Calendar;

public class Date {

	private int jour;
	private int mois;
	private int an;
	private int heure;
	private int minute;
	private int seconde;

	public Date() {
		Calendar calendar = Calendar.getInstance();
		jour = calendar.get(Calendar.DAY_OF_MONTH);
		mois = calendar.get(Calendar.MONTH)+1;
		an = calendar.get(Calendar.YEAR);
		heure = calendar.get(Calendar.HOUR);
		minute = calendar.get(Calendar.MINUTE);
		seconde = calendar.get(Calendar.SECOND);
		
	}

	@Override
	public String toString() {
		return  heure + ":" + minute + ":" + seconde + " " + jour + "/" + mois + "/" + an;
	}
	

}