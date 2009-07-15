/*
* int ATTRIBUTE = 1							 // int 1 is 0001
* flags = flags | ATTRIBUTE 				//set the last bit of flags to 1
* if ((flags & ATTRIBUTE) == ATTRIBUTE)		//if the last bit of flags is 1
* flags = flags & ~ATTRIBUTE 				//set the last bit of flags to 0
*/
public class Flag {
	static final int VISIBLE = 1;
	static final int DRAGGABLE = 2;
	static final int SELECTABLE = 4;
	static final int EDITABLE = 8;

	public static void main (String[] args) {
		int flags = 0;

		flags = flags | VISIBLE;	//set visible;
		System.out.println(flags);
		flags = flags | DRAGGABLE;	//set draggable;
		System.out.println(flags);

		if ((flags & VISIBLE) == VISIBLE) {
			if ((flags & DRAGGABLE) == DRAGGABLE) {
					System.out.println ("Flags are Visible and Draggable.");
			}
		}

		flags = flags & ~VISIBLE;
		System.out.println (flags);
		flags = flags & ~DRAGGABLE;
		System.out.println (flags);
	}
}
