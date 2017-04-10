import java.io.BufferedWriter;
import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.FileWriter;
import java.io.IOException;
import java.net.Socket;
import java.net.UnknownHostException;
import java.util.ArrayList;
import java.util.Scanner;

public class Cliente implements Runnable {
	
	Socket MyClient;
	DataInputStream stdIn;
	DataInputStream in;
	DataOutputStream os;
	String current_room; // current room he is in
	String current_command; // current command he is using
	boolean stop = false; // stop cycle
	String responseLine; // response from server
	String nome; // name of user
	boolean stop_register = false; // stop cycle for registry
	String current_name; // current name he is using

	String current_response; // current response
	File Friends = new File("Friends.txt"); // friends file
	ArrayList<String> Friendlist = new ArrayList<String>(); // loaded friends list
	File Cenas = new File(""); 
	byte[] file; //file in byte
	int partition;
	int count;
	ArrayList<String> belongsTo = new ArrayList<String>(); // lists of rooms the user belongs to
	
	
	Cliente() throws UnknownHostException, IOException{
		 MyClient = new Socket("mini.alunos.di.uevora.pt" , 143);
		 Friends.createNewFile();	// if it doesnt exist yet, create it
		 loadFriendlist(); // load it to memory
	}	
	
	
	// inverse of the function below
	public void bytetofile(String ficheiro, byte[] bFile) throws IOException{
	
		
		File temp = new File(ficheiro);
		temp.createNewFile();
		
	    //convert array of bytes into file
	    FileOutputStream fileOuputStream = 
                  new FileOutputStream(ficheiro); 
	    fileOuputStream.write(bFile);
	    fileOuputStream.close();
      
    }
	
	// file to byte 
	public byte[] filetobyte(File file) throws IOException{
		byte[] cenas = new byte[(int) file.length()];

	    FileInputStream fileInputStream = new FileInputStream(file);
        fileInputStream.read(cenas);
        fileInputStream.close();
        
        return cenas;     
        
	}

	// send the file, send part by part, with a delay of 0.5s after 200 bytes
	public void send(String filenum, byte[] cenas ) throws IOException, InterruptedException{
		
		for(int i = 0; i < cenas.length; i++)
		{
			os.writeBytes("SENDPART " + filenum + " " + cenas[i]);
			os.writeByte('\n');
			if(i%200==0){ // after 200
				Thread.sleep(500); // 0.5s delay so it doesnt timeout
			}
			
		}
		
		os.writeBytes("ENDFILE " + filenum); // file ended!
		os.writeByte('\n');
		
		System.out.println("System: File sent sucessfully\n");
	}
	
	
	// if the check fails, send message to channel so it can give an error response 
	public void sendstuff(String cenas) throws IOException, InterruptedException{
		os.writeBytes(cenas);
		os.writeByte('\n');
		
		Thread.sleep(1000);
	}
	
	// send a request for file to a user
	public void sendrequest(String user, String file ) throws IOException, InterruptedException{
		File temp  = new File(file);
		os.writeBytes("SENDFILE " + user+ " " + (int)temp.length() + " " + file);
		os.writeByte('\n');
		System.out.println("System: Sending request to "+user+"\n");
		Thread.sleep(1000);
		
	}
	
	// the user can accept the transfer
	public void aceptfile(String i) throws IOException, InterruptedException{
		os.writeBytes("ACCEPTFILE " + i);
		os.writeByte('\n');
		
		Thread.sleep(1000);
	}
	
	// the user can refuse to accept the transfer
	public void Refusefile(String i) throws IOException, InterruptedException{
		os.writeBytes("REFUSEFILE " + i);
		os.writeByte('\n');
		
		Thread.sleep(1000);
	}
	
	
	// the user can cancel the file at any given time of the transfer
	public void Abortfile(String i,String A) throws IOException, InterruptedException{
		os.writeBytes("ABORTFILE " + i +" "+ A);
		os.writeByte('\n');
		
		Thread.sleep(1000);
	}
	
	// meaning the file that was sent has ended
	public void endfile(String i) throws IOException, InterruptedException{
		os.writeBytes("ENDFILE " + i);
		os.writeByte('\n');
		
		Thread.sleep(1000);
	}
	
	// loads friends list to memory
	public void loadFriendlist() throws IOException{
		Scanner scannerFile = new Scanner(Friends);
		
		while(scannerFile.hasNextLine())
		{
			Friendlist.add(scannerFile.nextLine());
		}
		
		scannerFile.close();
		
		
	}
	
	// register a friend -> send it to file 
	public void registerFriend(String Cenas) throws IOException
	{
		BufferedWriter out = new BufferedWriter(new FileWriter("Friends.txt",true));
		out.write(Cenas);
		out.newLine();
		out.close();
		System.out.println("\nSystem: Friend Added! YAY FRIENDSHIP!!");
		loadFriendlist();
	}
	
	
	public void Close() throws IOException
	{
		MyClient.close();
	}

	// help section, this section will give detailed description of all the commands available to the user
	// upon entering the chat room
	public void help()
	{
		System.out.println("Available commands\n");
		System.out.println("Chat related: \n"
				+ "\t/pm <nome> <msg> - sends a private message to user <nome> \n"
				+ "\t/msg <channel> <msg> - sends message to channel <channel> \n");
		
		System.out.println("Registry related: \n"
				+ "\t/register [<email>] <password> - registers current name with password, with optional email\n"
				+ "\t/changenick <new_name> - changes user's name \n"
				+ "\t/recover - recovers a password from name sends it to email\n"
				+ "\t/registerfriend <name> - register <name> as friend\n");
		
		System.out.println("Channel Related: \n"
				+ "\t/changetopic [<room > <new_topic>] - changes the topic on room < room >, if no parameters are given then shows a list and ask user to choose \n"
				+ "\t/enter [<room>] - if no parameter is given then shows list of rooms, player can choose to enter or create room <room> \n "
				+ "\t/leaveroom [<room> <message>] - leaves room <room>, if no parameters are given, shows list and makes user choose \n"
				+ "\t/inroom [<room>] - returns a list of users in the room <room> if given the parameter, else gives the user list in all rooms he belongs to\n ");
		
		System.out.println("File Related: \n"
				+ "\t /sendrequest <name> <file> - send request to <name>\n"
				+ "\t /send <descriptor> - send file"
				+ "\t /refuse <descriptor> - refuses the file being sent to you\n"
				+ "\t /accept <descriptor> - accepts the file being sent to you \n"
				+ "\t /abort <descriptor> [<reason>] - aborts the file, you can give a reason\n");
		
		System.out.println("General: \n"
				+ "\t/userlist - returns a list of all the users in the chat\n"
				+ "\t/roomlist - returns a list of all channels in the chat\n"
				+ "\t/friendlist - returns user a list of his friends\n"
				+ "\t/help - all commands and descriptions\n "
				+ "\t/belong - returns all the rooms the user belongs to\n"
				+ "\t/leave [<message>] - leaves the chat with optional message\n");
		
		introduction();
	}
	
	// in short, what the user can do
	public void introduction()
	{
		System.out.println("System: In short, here's what the user can do: \n"
				+ "\t 1 - Register name and recover password\n"
				+ "\t 2 - Change name\n"
				+ "\t 3 - Send, accept, refuse, cancel files\n"
				+ "\t 4 - Send messages to a channel or to a user (via private message)\n"
				+ "\t 5 - Enter, leave rooms, see information about room and change their topic\n"
				+ "\t 6 - See all the users in chat\n"
				+ "\t 7 - See all rooms in chat\n"
				+ "\t 8 - See all rooms user belongs to\n"
				+ "\t 9 - Add friends\n"
				+ "\n Above are all the commands and descriptions\n");
	}
	
	// when the player first enters the chat, he must enter a nick name
	// with optional password, if no password is given then it if nick accepted it becomes a temporary nick
	@SuppressWarnings("deprecation")
	public void register() throws IOException, InterruptedException 
	{
		stop_register = false;
		Scanner scan,scan2;
		
		
		while(!stop_register) // until a nick is accepted -> infinite loop
		{
			System.out.println("Informação:\n"
					+ "\tUm nickname pode ser constituido por letras, numeros, hifens,\n"
					+ "\tunderscores, parenteses e chavetas\n"
					+ "\tnao pode conter cedilhas nem acentos nem espaços\n");
			
			
			System.out.print("Login: ");
			scan = new Scanner(System.in);
			nome = scan.nextLine();
			
			String[] array = nome.split(" "); // split the nick but without the spaces. 
			
			if(array.length > 1) // if the array length is > 1 then it means it had spaces
				System.out.println("System: Invalid name");
			
			
			
			else
			{
				System.out.print("Password (no password means temporary nick): ");
				scan2 = new Scanner(System.in);
				String pass = scan2.nextLine(); // get the entire line
			
				if(!pass.equals("")){ // if there is a password 
					os.writeBytes("NICK "+nome+" \\"+pass);}
				else
					os.writeBytes("NICK "+nome); //else...
			
				os.writeByte('\n');
				
				Thread.sleep(1000);
			
			
			// server response
			
				String response = in.readLine();
			
				if( response.equals("OK_NICK "+nome))
				{
					System.out.println("\nSystem: Login Accepted\n");
					if(pass.equals(""))
						System.out.println("System: Nickname set to temporary");	
					stop_register = true; // stop cycle
				}
				else if( response.equals("ERR_NICK_INUSE "+array[0]))
					System.out.println("\nSystem: Nick already in use - Try again\n");
				
				else if( response.equals("ERR_NICK_ISREG "+array[0]))
					System.out.println("\nSystem: Nickname already been registered - Try again\n");
				
				else if( response.equals("ERR_NICK_WRONGPASS "+array[0]))
						System.out.println("\nSystem: Wrong password - Try again\n");

			}
		}
		
		current_room = "@global"; // default channel
		System.out.println("Transfered to room: "+current_room);
		
		os.writeBytes("ENTER "+current_room);
		os.writeByte('\n');
		
		Thread.sleep(1000);
		
		belongsTo.add(current_room); // add it to the rooms the user belongs to
		
	}

	// all commands available
	//#################################################################################################
	//#################################################################################################
	public void commands(String userInput) throws IOException, InterruptedException 
	{
		
		String[] array = userInput.split(" ");
		
		if(array[0].equals("/help")) // get help
			help();
		
		else if(array[0].equals("/inroom")) // who is in the room
			seeRoom(array);
		
		else if(array[0].equals("/leave")) // leave the chat
			quit(array);
		
		else if(array[0].equals("/leaveroom")) // leave room X
			roomLeave(array);
		
		else if(array[0].equals("/changetopic")) // change the topic of the room
			changeTopic(array);
		
		else if(array[0].equals("/register"))  // register current nick
			register_name(array);
		
		else if(array[0].equals("/changenick")) // change the nick
			change_nick(array);
		
		else if(array[0].equals("/pm")) // send a private message to user
			msg_private(array);
		
		else if(array[0].equals("/enter")) // enter a room
			enter_room(array);
		
		else if(array[0].equals("/roomlist")) // check rooms in chat
			seeEverything(array);
		
		else if(array[0].equals("/userlist")) // check users in chat
			seeEverything(array);
		
		else if(array[0].equals("/registerfriend")) // register a friend
		{
			registerFriend(array[1]);
		}
		else if(array[0].equals("/sendrequest")) // send request
		{
			Cenas = new File(array[2]);
			sendrequest(array[1],array[2]);
		}
		
		else if(array[0].equals("/send")){	 // after accepted, send file
				send(array[1],filetobyte(Cenas));
			
		}
		else if (array[0].equals("/accept")){ // accept transfer request
			aceptfile(array[1]);
		}
		else if (array[0].equals("/end")){ // end of file (not used)
			endfile(array[1]);
		}
		else if (array[0].equals("/refuse")){ // refuse transfer request
			Refusefile(array[1]);
		}
		else if (array[0].equals("/abort")){ // cancel file
			Abortfile(array[1],array[2]);
		}
		
		else if (array[0].equals("/recover")){ // recover password
			recover_password(array);
		}
		
		else if (array[0].equals("/friendlist")){ // user friend list
			System.out.println("\nList of friends: \n");
			for(int i =0; i<Friendlist.size(); i++)
			System.out.println("\t"+Friendlist.get(i));
		}
		
		else if(array[0].equals("/belong")) // rooms the user belongs to
			belongsTo(array);
		else if (array[0].equals("/msg"))// if nothing then its a message to the channel
			msg_channel(array);
		else
			sendstuff(userInput); // any other command goes in here
	}
	
	// the rooms the user belongs to
	private void belongsTo(String[] array) {
		System.out.println("List of rooms you are in: \n" );
		for(int i = 0; i < belongsTo.size(); i++)
		{
			System.out.println("\tRoom: "+belongsTo.get(i)+"\n");
		}
	}
	
	// sends a recover request to server to recover password
	private void recover_password(String[] array) throws IOException, InterruptedException 
	{
		if (array.length > 1) // to many arguments
			System.out.println("System: To many arguments\n");
		else{
			os.writeBytes("RECOVER "+nome); // recover
			os.writeByte('\n');
			
			Thread.sleep(1000);
		}
	}
	
	// either see all users in chat, or all rooms in chat
	private void seeEverything(String[] array) throws IOException, InterruptedException {
		if(array.length > 1)
			System.out.println("System: To many arguments\n");
		else if(array.length < 1)
			System.out.println("System: Missing arguments\n");
		else	
		{
			if(array[0].equals("/roomlist")) // see all rooms
			{
				os.writeBytes("RLIST");
				os.writeByte('\n');
				System.out.println("\n Room list: \n");
			}
			if(array[0].equals("/userlist")) // see all users
			{
				os.writeBytes("ULIST");
				os.writeByte('\n');
				System.out.println("\n User list: \n");
			}
			Thread.sleep(1000);
		}
		
	}


	
	// enters or creates a room
	private void enter_room(String[] array) throws IOException, InterruptedException {
		if(array.length > 2)
			System.out.println("System: To many arguments");
		
		// if the user did not include a room in the input then it shows the list of existing rooms
		else if(array.length < 2){
			
			System.out.println("List of existing rooms: \n");
			os.writeBytes("RLIST");
			os.writeByte('\n');
		
			Thread.sleep(1000);
		
			System.out.print("Room to enter/create: ");
			Scanner scan = new Scanner(System.in);
		
			String room = scan.next();
		
			if(!room.contains("@")) // if the input has no @
				room = "@"+room;
		
			os.writeBytes("ENTER "+room);
			os.writeByte('\n');
			
			Thread.sleep(1000);
			
			if(!belongsTo.contains(room)) // if the room he wants to enter/create already is in the list
				belongsTo.add(room); // add it to list
		}
		else{

			if(!array[1].contains("@")) // if input has a room
				array[1] = "@"+array[1];
			
			os.writeBytes("ENTER "+array[1]);
			os.writeByte('\n');
			
			Thread.sleep(1000);
			
			if(!belongsTo.contains(array[1])) // if the room he wants to enter/create already is in the list
				belongsTo.add(array[1]); // add it to list
		}
	}
	
	
	// send message to channel
	private void msg_channel(String[] array) throws IOException, InterruptedException 
	{
		if(array.length < 3) // not enough arguments
			System.out.println("System: Missing arguments\n");
		else{
			if (!array[1].contains("@")) // if channel doesnt contain @ the system does it for the user
				array[1] = "@"+array[1];
			
			String msg = array[2]; // message
			for(int i = 3; i < array.length; i++)
				msg += " "+array[i];
			
			os.writeBytes("MSG "+array[1]+" \\"+msg);
			os.writeByte('\n');
			
			System.out.println("\n["+array[1]+"] "+nome+" : "+msg+"\n");
			
			Thread.sleep(1000);
			
			
		}
	}

	// send a private message to a user
	private void msg_private(String[] array) throws IOException, InterruptedException 
	{	
		if(array.length < 3) // not enough arguments
			System.out.println("System: Missing arguments\n");
		else{
			String msg = array[2]; // generate message
			for(int i = 3; i < array.length; i++)
				msg += " "+array[i];
			
			
			os.writeBytes("MSG "+array[1]+ " \\" +msg);
			os.writeByte('\n');
			
			System.out.println("\n[PM] To "+array[1]+" : "+msg.substring(1, msg.length())+"\n");
			
			Thread.sleep(1000);
			
			
		}
	}

	// leaves the room, if its a room where he belongs, then remove it from the list
	// if no room is given, give list of rooms he belongs to and make user choose one
	private void roomLeave(String[] array) throws IOException, InterruptedException {
		if(array.length < 2) // just the command it self with no message and no room
		{
			System.out.println("Rooms you belong to: \n");
			for(int i = 0; i < belongsTo.size(); i++)
				System.out.println("\t"+belongsTo.get(i));
		
			System.out.print("Room to leave: "); // choose room to leave
			Scanner scan = new Scanner(System.in);
			String room = scan.next();
			
			System.out.println("Leave message: "); // choose to send message
			Scanner scan2 = new Scanner(System.in);
			String msg = scan2.nextLine();
			
			if(!room.contains("@")) // if input has no @, then adds it
				room = "@"+room;
			 
			if(!msg.equals("")) // if no message was given
				os.writeBytes("LEAVE "+room);
			else
				os.writeBytes("LEAVE "+room+" "+msg);
			
			os.writeByte('\n');
			Thread.sleep(1000);
		}
		else{
			if(!array[1].contains("@")) // if input has no @, then adds it
				array[1] = "@"+array[1];
			
			if(array.length > 2)
				os.writeBytes("LEAVE "+array[1]+" "+array[2]);
			else
				os.writeBytes("LEAVE "+array[1]);
			
			if(belongsTo.contains(array[1]))
				belongsTo.remove(array[1]);
			os.writeByte('\n');
			Thread.sleep(1000);
		}
	}

	// changes the user nick
	private void change_nick(String[] array) throws IOException, InterruptedException 
	{
		if(array.length > 2){
			String pass = array[2];
			for(int i = 3 ; i < array.length; i++) // get password
				pass += " "+array[i]; // reconstruct password
			
			os.writeBytes("NICK "+array[1]+ " "+pass); 
			os.writeByte('\n');
		}else{ // it has no password
			os.writeBytes("NICK "+array[1]); 
			os.writeByte('\n');
		}
		Thread.sleep(1000);
	}



	// register the current name given the optional email and password
	
	private void register_name(String[] array) throws IOException, InterruptedException 
	{
		if(array.length < 2 ) // not enough arguments
			System.out.println("System: Missing arguments\n");
		
		else{
			String msg = "";
			//System.out.println(array.length);
			if(array[1].contains("@")) // if there is @ means there is a en email attached
			{ // there is mail	
				for(int i = 2; i < array.length; i++) // password
					msg += array[i]+" "; 
			
					os.writeBytes("REGISTER "+nome+" "+ array[1]+" "+ msg);
			}
			else
			{
					for(int i = 1; i < array.length; i++) //password
						msg += array[i]+" "; 
					os.writeBytes("REGISTER "+nome +" \\"+ msg);
			}
				os.writeByte('\n');
				
				Thread.sleep(1000);
			}
	}


	// if the user quits the chat, then it ends the cycle in Main. 
	// user can choose to leave with a message
	private void quit(String[] array) throws IOException, InterruptedException
	{
		
			if(array.length > 1) // there is a message attached
			{
				String msg = array[1]; // create the message 
				for(int i = 2; i < array.length ; i++)
					msg += array[i];
				
				os.writeBytes("QUIT "+array[1]);
				
			}else
				os.writeBytes("QUIT");
		
			os.writeByte('\n');
			
			Thread.sleep(1000);
			stop = true;
	}

	// change topic on a room
	private void changeTopic(String[] array) throws IOException, InterruptedException 
	{
		String topic; // topic
		String room;
		if(array.length == 1)
		{
			System.out.println("List of existing rooms: \n");
			os.writeBytes("RLIST");
			os.writeByte('\n');
		
			Thread.sleep(1000);
		
			System.out.print("Room to change topic: ");
			Scanner scan = new Scanner(System.in);
		
			 room = scan.next();
			
			System.out.print("Topic: ");
			Scanner scan2 = new Scanner(System.in);
			
			topic = scan2.nextLine();
			
		}
		
		else if(array.length > 2){
			topic = array[2];
			for(int i = 3; i < array.length; i++)
				topic += " "+array[i];
			
			topic = array[2];
			room = array[1];
		}
		else{
			 topic = ""; // input's lenght is < 2 means the topic is blank
			 room = array[1];
		}
		if(!room.contains("@")) // user can enter a room with @, if so, it adds it
			room = "@"+room;
		
		
		os.writeBytes("TOPIC "+room+" "+topic); 
		os.writeByte('\n');
		Thread.sleep(1000);
	}

	// se the people in the room of choice. unless the user didnt specify a room, then returns all the users in the rooms the user belongs to
	private void seeRoom(String[] array) throws IOException, InterruptedException 
	{
		if(array.length < 2) //gives list of all users in the rooms he is in
		{
			for(int i = 0; i < belongsTo.size(); i++) // go trough the list of rooms he belongs to
			{
				os.writeBytes("WHO "+belongsTo.get(i));
				os.writeByte('\n');
				Thread.sleep(1000);
			}
		}
			
		else if(array.length > 2)
			System.out.println("System: To many arguments\n");
		else
		{	
			os.writeBytes("WHO "+array[1] );
			os.writeByte('\n');
			Thread.sleep(1000);
		}	
	}

	//#################################################################################################
	//#################################################################################################
	//#################################################################################################
	@SuppressWarnings("deprecation")
	public static void main(String[] args) throws IOException, InterruptedException 
	{
		Cliente client  = new Cliente();
		
		DataInputStream stdIn = new DataInputStream(System.in);			
		client.os = new DataOutputStream(client.MyClient.getOutputStream());
		client.in =  new DataInputStream(client.MyClient.getInputStream());
		
		String userInput = "";
		System.out.println("Login w/ password or Login w/out password");
		client.register(); //ask user to register
		
		Thread t = new Thread(client); // threaded client
	
		
		System.out.println('\n');
		client.help(); // let the user see all commands available when he enters room
	
		t.start(); // start thread
		while(!client.stop)		//until user leaves the chat room, continues on a infinite loop
		{
			userInput = stdIn.readLine();	
			client.commands(userInput);	// check user input
			
			System.out.println("\n");
			
		}   
		
		// end connection 
		t.join();
		client.os.close();
		client. in.close();
        client.Close();
        
	}
	//#################################################################################################
	//#################################################################################################
	//#################################################################################################

	// threading related below
	
	// register responses
	//#################################################################################################
	void register_response(String responseLine, String[] response)
	{
		if(response[0].equals("ERR_ALREADYREGISTERED")) // nickname registered
			System.out.println("System: "+response[1]+" has already been registered\n");
		
		else if(response[0].equals("ERR_NOTALLOWED")) // you are not allowed to
			System.out.println("System: "+response[1]+" is invalid\n");
		
		else if(response[0].equals("OK_NICKREGISTERED")) // register ok
			System.out.println("System: "+response[1]+" has been registered sucessfully\n");
		
	}

	// nick related responses
	//#################################################################################################
	void nick_response(String responseLine ,String[] response)
	{
		if(response.length > 1){
		 if(responseLine.equals("OK_NICK "+ response[1])) // nick ok
   		  	System.out.println("Nick has been changed sucessfully!\n");
		 
		 else if(responseLine.equals("ERR_NICK_INUSE "+response[1])) // nick is in use by someone else
			System.out.println("\nNick already in use - Try again\n");
			
		 else if(responseLine.equals("ERR_NICK_ISREG "+response[1])) // nick is already registed
			System.out.println("\nNickname already been registered - Try again\n");
			
		 else if(responseLine.equals("ERR_NICK_WRONGPASS "+response[1])) // wrong pass
			System.out.println("\nWrong password - Try again\n");
		 
		 
		 // recover password from nick related responses
		 else if(response[0].equals("ERR_NOTREGISTERED")) // user is not registered
			 System.out.println("System: User "+response[1]+" is not a registered user");
		 
		 else if(response[0].equals("ERR_NOEMAIL")) // no email attached
			 System.out.println("System: User "+response[1]+" does not have a email associated");
		 
		 else if(response[0].equals("OK_RECOVER")) // recovery ok
			 System.out.println("System: Recover sucessful. Password has been sent to email");
		 
		 else if(response[0].equals("NICKCHANGE")) // nick name change
			 System.out.println("System: User +"+response[1]+" has changed his nick to "+response[2]);
		 
		 else if(response[0].equals("ERR_NICK")) // nickname invalid
			 System.out.println("System: Nickname "+response[1]+" is invalid or there was an error");
		 
		 else if(response[0].equals("ERR_NONICK")) // must have a nick before using commands
			 System.out.println("System: Must create nick before using any other commands");
		}
	}
	
	// quit related responses
	//#################################################################################################
	void quit(String responseLine, String[] response)
	{
		if(response[0].equals("USERQUIT")){
			
			if(response.length <= 2){
				if(Friendlist.contains(response[1])) // is friend?
					System.out.println("User "+response[1]+"* has been disconnected\n");
				else
					System.out.println("User "+response[1]+" has been disconnected\n");
			}else
			{
				String quit = response[2].substring(1, response[2].length());
				for(int i = 3; i < response.length; i++)
					quit += " "+response[i]; // reconstruct message
				
				if(Friendlist.contains(response[1])) // is friend?
					System.out.println("User "+response[1]+"* has been disconnected\n" + "\tMessage: "+quit+"\n");
				else
					System.out.println("User "+response[1]+" has been disconnected\n" + "\tMessage: "+quit+"\n");
			}
		}
	}
	
	// room related responses
	//#################################################################################################
	void room_related(String response, String[] response_2)
	{
		// enter room responses
		if(response_2[0].equals("USERENTER")) // user has entered
			if(Friendlist.contains(response_2[2])){ // is friend?
				System.out.println("User "+response_2[2]+ "*"+" has entered channel "+response_2[1]+"\n");
			}
			else{
				System.out.println("User "+response_2[2]+" has entered channel "+response_2[1]+"\n");
			}
		
		else if(response_2[0].equals("INROOM")) // who is in the room
		{
			String users = "";
			System.out.println("Users in room "+response_2[1]+": \n");
			 
			if(Friendlist.contains(response_2[2].substring(1, response_2[2].length()))) // is friend?
			{
				users = "\t"+response_2[2].substring(1, response_2[2].length())+"*\n";
			}
			else
				users = "\t"+response_2[2].substring(1, response_2[2].length())+"\n";
			
			for(int i = 3; i < response_2.length; i++) // reconstruct message
			{
				if(Friendlist.contains(response_2[i])) // is friend?
					users += "\t"+response_2[i] +"*\n"; 
				else
					users += "\t"+response_2[i] +"\n";
			}
			
			System.out.println(users+"\n");
		}
		else if(response_2[0].equals("ROOMINFO")) // room info 
		{
			System.out.println("Room name: "+response_2[1]);
			System.out.println("Room topic: "+response_2[2].substring(1, response_2[2].length()));
			System.out.println("\n");
		}
		
		
		// leave room responses
		else if(response_2[0].equals("ERR_NOTINROOM")){ // you cant leave a room you are not in
			System.out.println("System: Invalid room, you are not part of this room\n");
		}
		else if(response_2[0].equals("USERLEFT")) // user has left
			if(response_2.length > 2)
			{
				String leave = response_2[3];
				for(int i = 4; i < response_2.length; i++)
					leave += " "+response_2[i]; // reconstruct message
				
				if(Friendlist.contains(response_2[2])){	// is friend?
					System.out.println("User "+response_2[2]+ "* has left "+response_2[1]+"\n");}
				else{
					System.out.println("User "+response_2[2]+ " has left "+response_2[1]+"\n");
				}
				
				System.out.println("Msg: "+leave+"\n");
			}
			else{
				if(Friendlist.contains(response_2[2])){	// is friend?
					System.out.println("User "+response_2[2]+ "* has left "+response_2[1]+"\n");}
				else{
					System.out.println("User "+response_2[2]+ " has left "+response_2[1]+"\n");
				}
				
			}
		else if(response_2[0].equals("ERR_NOROOM")) // wrong room name
			System.out.println("System: Message not delivered, Invalid room name\n");
		
		else if(response_2[0].equals("ERR_ROOMNAME")) // wrong room name
			System.out.println("System: Message not delivered, Invalid room name\n");
		
		else if(response_2[0].equals("TOPICSET")) // change topic
			if(response_2.length > 2){
				if(Friendlist.contains(response_2[2])){	// is friend?
					System.out.println("System: Room "+response_2[1]+" topic has been changed to "+response_2[3].substring(1, response_2[3].length()) + " by "+response_2[2]+"*\n");
					}
				else{
					System.out.println("System: Room "+response_2[1]+" topic has been changed to "+response_2[3].substring(1, response_2[3].length()) + " by "+response_2[2]+"\n");
				}
			}else{
				
				if(Friendlist.contains(response_2[2])){	// is friend?
					System.out.println("System: Room "+response_2[1]+ "topic has been removed by "+response_2[2]+"*\n");
					}
				else{
					System.out.println("System: Room "+response_2[1]+ "topic has been removed by "+response_2[2]+"\n");
					}
		
			}
		else if(response_2[0].equals("USERLIST")) // user list
		{
			String users = "\t"+response_2[1].substring(1,response_2[1].length())+"\n";
			for(int i = 2; i <  response_2.length-1; i++)
			{
				if(!response_2[i].equals("USERLIST")) // get user list
				{ // users list
					if(Friendlist.contains(response_2[i])) // is friend?
						users += '\t'+response_2[i]+"*\n";
					else
						users += '\t'+response_2[i]+"\n";
				}
			}
			
			System.out.println(users+"\t"+response_2[response_2.length-1]);
		}
		else if(response_2[0].equals("ROOM"))
		{
			System.out.println("Room "+response_2[1]+"\n"
					+ "\tNumber of users: "+response_2[2]+"\n");
			
			if(response_2.length > 3){
				String topic = response_2[3];
				
				for(int i = 4; i < response_2.length; i++) // topic
					topic += " "+response_2[i]; // reconstruct topic
				
				System.out.println("\tTopic: "+response_2[3].substring(1, response_2[3].length())+"\n");
			}
		}
	}
	
	
	// chat related responses
	//#################################################################################################
	public void chat_related(String response, String[] array)
	{
		String msg = "";
		if(array[0].equals("ERR_NOUSER")) // user doesnt exist
			System.out.println("System: User "+array[1]+" does not exist\n");
		
		else if(array[0].equals("ERR_UNDELIVERED")) // message wasnt delivered
		{
			System.out.println("System: Message not delivered \n");
			System.out.println("Error: "+array[2].substring(1, array[2].length()));
		}

		
		// msg from user
		else if (array[0].equals("MSGFROM"))
		{
			if(array[1].charAt(0) == '@')
			{
				msg = getRestOfMessageChannel(array); // get reconstructed message
				if(array.length > 3)
				{
					System.out.println("System: You have received a message, to reply /msg "+array[1] +" <msg>");
					
					if(Friendlist.contains(array[2]))
						System.out.println("["+array[1]+"]"+" "+array[2]+"*: "+msg+"\n");
					else
						System.out.println("["+array[1]+"]"+" "+array[2]+": "+msg+"\n");
				}	
			}
			else
			{
				msg = getRestOfMessagePrivate(array); // get reconstructed message
				if(Friendlist.contains(array[1]))
				{
					System.out.println("System: You have received a message, to reply /pm "+array[1]+"* <msg>");
					System.out.println("[PM] From "+" "+array[1]+"* : "+msg+"\n");
				}
				else
				{
					System.out.println("System: You have received a message, to reply /pm "+array[1]+" <msg>");
					System.out.println("[PM] From "+" "+array[1]+" : "+msg+"\n");
				}
					
			}
		}
	}

	// channel message 
	//#################################################################################################
	public String getRestOfMessageChannel(String[] array) 
	{
		String msg = array[3].substring(1, array[3].length());
		for(int i = 4;  i < array.length; i++ )
			msg += " "+array[i]; // reconstruct message
		
		return msg;
	}
	
	// private msg
	//#################################################################################################
	public String getRestOfMessagePrivate(String[] array)
	{
		String msg = array[2].substring(1, array[2].length());
		for(int i = 3;  i < array.length; i++ )
			msg += " "+array[i]; // reconstruct message

		return msg;
	}
	
	private void err_txt(String responseLine, String[] response)
	{
		if(response[0].equals("ERR_TXT")){
			String error = response[1].substring(1, response[1].length());
			
			for(int i = 2; i < response.length; i++) // error description
				error += " "+response[i]; // reconstruct error description
			
			System.out.println("System: Error occurred, "+error);
		
		}
		
	}
	
	// thread on the run
	//#################################################################################################
	@SuppressWarnings("deprecation")
	@Override
	public void run() 
	{
		    try 
		    {
		    String[] array;
		    byte[] array2;
		      while ((responseLine = in.readLine()) != null) 
		      {
		    	  current_response = responseLine;
		    	
		    	  array = responseLine.split(" "); // split the message, reconstruction comes later
		    	 
		    	  nick_response(current_response,array); // check for nick related
		    	  
		    	  quit(current_response,array); // check for leave input
		    	  
		    	  room_related(current_response,array); // room related responses
		    	  
		    	  chat_related(current_response,array); // chat related responses
		    	  
		    	  register_response(current_response, array); // register related
		    	  
		    	  file_response(current_response,array); // check for file response
		    	  
		    	  err_txt(current_response,array); // check for error response

		      }	
		    } 
		    catch (IOException e) {
		        System.err.println("IOException:  " + e);
		    }
	}
	
	// responses by file commands
	private void file_response(String current_response2, String[] array) throws IOException {
		
		if(array[0].equals("FILETRANSFER"))
		{
			file = new byte[Integer.parseInt(array[2])];
			if(Friendlist.contains(array[1])){
				System.out.println("System: User "+array[1] +"* is sending file. Details: \n"
					+ "\tFile Size: "+array[2]+"\n" + "\tDescriptor To Use:" +array[3]+"\n"
							+ "\tFile Name: "+array[4].substring(1, array[4].length())+"\n");
			}
			else
			{
				System.out.println("System: User "+array[1] +" is sending file. Details: "
						+ "\tFile Size: "+array[2]+"\n" + "\tDescriptor To Use:" +array[3]+"\n"
								+ "\tFile Name: "+array[4].substring(1, array[4].length())+"\n");
			}
			
			System.out.println("System: To accept /accept <descriptor> to refuse /refuse <descriptor>\n");
		}
		else if(array[0].equals("FILEPART"))
		{
			for(int i = 2; i < array.length; i++)
			{
				if(array[i].contains("\\"))
					array[i] = array[i].substring(1, array[i].length());
				file[i] = (byte) Integer.parseInt(array[i]);
				
			}

			bytetofile(array[1]+".txt",file);
		}
		
		else if(array[0].equals("NEWTRANSFER"))
		{
			String file_name = array[2];
			for(int i = 3; i<array.length; i++)
				file_name += " "+array[i];
			System.out.println("System: User "+array[1]+" sending "+file_name+ " has been accepted by the server");
		}
			
		else if(array[0].equals("FILEACCEPT"))
		{
			System.out.println("System: File has been accepted");
		}
		else if(array[0].equals("FILEREFUSE"))
			System.out.println("System: File has been refused");
		
		else if(array[0].equals("ERR_NOTRANSFER"))
			System.out.println("System: Error, there is no transfer or transfer has been concluded ");
		
		else if(array[0].equals("ABORTED"))
			System.out.println("System: Transfer has been canceled");
		else if(array[0].equals("FILEABORT"))
		{
			String reason = "";
			if(array.length > 3){
				 reason = array[2].substring(1, array[2].length());
				for(int i = 3; i < array.length; i++) // reconstruct reason
					reason += " "+array[i];
			}
			System.out.println("System: Transfer has been canceled\n"
					+ "\tReason: "+reason);
		}
		else if(array[0].equals("FILEEND"))
			System.out.println("System: File has been received sucessfuly!");
		
	}       
}