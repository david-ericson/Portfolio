package com.neumont.dericson.chess;

import com.neumont.dericson.chess.MoveManager.BlockedMove;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.HashSet;
import java.util.LinkedList;
import java.util.List;
import java.util.Map;
import java.util.Set;

import com.neumont.dericson.piece.types.King;

public class CheckManager {
	//private static Map<Piece, Set<PieceAttackBlockers>> pieceAtks;
	private static Map<Square, Map<Piece, PieceBlockers>> allAttackers;
	private static Map<Piece, PieceInfo> pieceInfo;
	private static King lightKing, darkKing;
	
	private static class PieceBlockers{
		private Set<Piece> pieceInfo;
		
		public PieceBlockers(Set<Piece> pieces){
			pieceInfo = pieces;
		}
		
		public void removeBlocker(Piece blocker){
			pieceInfo.remove(blocker);
		}
		
		public boolean hasBlocker(Piece blocker){
			return pieceInfo.contains(blocker);
		}
		
		public void addBlocker(Piece blocker){
			pieceInfo.add(blocker);
		}
		
		public void clearBlockers(){
			pieceInfo.clear();
		}
		
		public int getNumBlockers(){
			return pieceInfo.size();
		}
		
		public Set<Piece> getBlockers(){
			return pieceInfo;
		}
	}
	
	private static class PieceInfo{
		private Map<Square, SquareOrigin> nextSquares;
		private Map<Piece, List<Square>> imBlocking;
		
		public PieceInfo(){
			nextSquares = new HashMap<>();
			imBlocking = new HashMap<>();
		}
		
		public void putSquare(Square start, Square next, Square origin){
			nextSquares.put(start, new SquareOrigin(origin, next));
		}
		
		public void clearMoves(){
			nextSquares.clear();
		}
		
		public Square getNextSquare(Square start){
			Square ret = (nextSquares.get(start)!= null)?nextSquares.get(start).square:null;
			return ret;
		}
		
		public List<Square> getSquaresImBlockingForPiece(Piece p){
			return imBlocking.get(p);
		}
		
		public Square getOriginOf(Square find){
			return nextSquares.get(find).getOrigin();
		}
		
		public Set<Piece> getImBlockingKeys(){
			return imBlocking.keySet();
		}
		
		public Set<Square> getMoves(){
			return nextSquares.keySet();
		}
		
		public void removeSquaresImBlockingForPiece(Piece p){
			if(imBlocking.get(p) != null){
				imBlocking.get(p).clear();
			}
		}
		
		public void addSquareImBlockingForPiece(Piece p, Square blocked){
			List<Square> squares = imBlocking.get(p);
			if(squares == null){
				squares = new ArrayList<>();
				imBlocking.put(p, squares);
			}
			squares.add(blocked);
		}
	}
	
	private static class SquareOrigin{
		private Square origin;
		public Square square;
		
		public SquareOrigin(Square origin, Square square){
			this.origin = origin;
			this.square = square;
		}
		
		public Square getOrigin(){
			return origin;
		}
	}
	
	public static void create(King lKing, King dKing){
		allAttackers = new HashMap<>();
		pieceInfo = new HashMap<>();
		lightKing = lKing;
		darkKing = dKing;
	}
	
	public static void testMethod(){
		for(Piece p: pieceInfo.keySet()){
			if(p.boardId == 'q' && p.teamId==0){
				Square s = BoardManager.findPiece(p);
				PieceInfo test = pieceInfo.get(p);
			}
		}
	}
	
	public static void transferBlocking(Piece from, Piece to){
		Set<Piece> blocking = pieceInfo.get(from).getImBlockingKeys();
		for(Piece p: blocking){
			for(Square s: pieceInfo.get(from).getSquaresImBlockingForPiece(p)){
				pieceInfo.get(to).addSquareImBlockingForPiece(p, s);
			}
		}
	}
	
	public static void pieceWasMoved(Piece p, Square moveFrom, Square moveTo){
		Map<Piece, PieceBlockers> attackers = allAttackers.get(moveTo);
		if(attackers != null){
			for(Piece piece : attackers.keySet()){
				if(!piece.equals(p)){
					changeSquares(piece, p, moveTo);
				}
			}
		}
		PieceInfo blocker = pieceInfo.get(p);
		boolean isDone = false;
		
		for(Piece piece: blocker.getImBlockingKeys()){
			isDone = false;
			List<Square> squaresHit = blocker.getSquaresImBlockingForPiece(piece);
			while(squaresHit.size() > 0 && !isDone){
				if(squaresHit.get(0).equals(moveTo)){
					isDone = true;
				}
				else{
					Square wasBlocked = squaresHit.get(0);
					allAttackers.get(wasBlocked).get(piece).removeBlocker(p);
					squaresHit.remove(0);
				}
			}
		}
		if(InputManager.getCurrCommand().equals("c3d5: ")){
			int i = 0;
		}
		setupAttacks(p, moveTo);
		Set<Piece> atkrs = allAttackers.get(BoardManager.getSquare(10)).keySet();
		for(Piece pic: atkrs){
			if(pic.name.equals("Knight")){
				for(Piece pc: allAttackers.get(BoardManager.getSquare(10)).get(pic).getBlockers()){
					System.out.println(InputManager.getCurrCommand() + pc.teamId+pc.name);
				}
			}
		}
	}
	
	private static void changeSquares(Piece attacker, Piece newBlocker, Square here){
		PieceBlockers pb = allAttackers.get(here).get(attacker);
		if(attacker.teamId == newBlocker.teamId){
			pb.addBlocker(newBlocker);
		}
		Square nextSquare = pieceInfo.get(attacker).getNextSquare(here);
		while(nextSquare != null){
			allAttackers.get(nextSquare).get(attacker).addBlocker(newBlocker);
			nextSquare = pieceInfo.get(attacker).getNextSquare(nextSquare);
		}
	}
	
	public static void setupAttacks(Piece piece, Square start){
		if(pieceInfo.get(piece) == null){
			pieceInfo.put(piece, new PieceInfo());
		}
		clearAttacks(piece);
		pieceInfo.get(piece).clearMoves();
		MoveManager.getPossibleMoves(piece.attackPattern, start, piece.teamId, true);
		List<BlockedMove> moves = MoveManager.getSquares();
		for(int i=0; i<moves.size(); i++){
			Square first = moves.get(i).getMove();
			if(allAttackers.get(first) == null){
				allAttackers.put(first, new HashMap<Piece,PieceBlockers>());
			}
			List<Piece> blockingMe = moves.get(i).getBlockers();
			Set<Piece> actuallyBlocking = getActualBlockers(blockingMe, piece, first);
			allAttackers.get(first).put(piece, new PieceBlockers(actuallyBlocking));
			Square second = (i+1<moves.size())?moves.get(i+1).getMove():null;
			if(second != null && !moves.get(i).getOrigin().equals(moves.get(i+1).getOrigin())){
				pieceInfo.get(piece).putSquare(first, null, moves.get(i).getOrigin());
				first = second;
				second = (i+1<moves.size())?moves.get(i+1).getMove():null;
			}
			pieceInfo.get(piece).putSquare(first, second, moves.get(i).getOrigin());
		}
	}
	
	private static void clearAttacks(Piece piece){
		for(Square s: pieceInfo.get(piece).getMoves()){
			for(Piece p: allAttackers.get(s).get(piece).getBlockers()){
				pieceInfo.get(p).removeSquaresImBlockingForPiece(piece);
			}
			allAttackers.get(s).remove(piece);
		}
	}
	
	private static Set<Piece> getActualBlockers(List<Piece> blockingMe, Piece piece, Square here){
		Set<Piece> result = new HashSet<>();
		for(Piece p: blockingMe){
			if((p.boardId != 'k' || (p.boardId == 'k' && p.teamId == piece.teamId))){
				if(pieceInfo.get(p) == null){
					pieceInfo.put(p, new PieceInfo());
				}
				result.add(p);
				pieceInfo.get(p).addSquareImBlockingForPiece(piece, here);
			}
		}
		return result;
	}
	
	public static void setPieceCanAttackSquare(Piece p, Square canAttack, Set<Piece> currBlockers){
		Map<Piece, PieceBlockers> mapBlockers = allAttackers.get(canAttack);
		if(mapBlockers == null){
			mapBlockers = new HashMap<>();
		}
		PieceBlockers pb = new PieceBlockers(currBlockers);
		mapBlockers.put(p, pb);
		allAttackers.put(canAttack, mapBlockers);
		for(Piece piece: currBlockers){
			PieceInfo found = pieceInfo.get(piece);
			if(found == null){
				found = new PieceInfo();
				pieceInfo.put(piece, found);
			}
			found.addSquareImBlockingForPiece(p, canAttack);
		}
	}
	
	public static boolean isInCheck(int teamToCheck){
		boolean inCheck = false;
		King k = (lightKing.teamId == teamToCheck)?lightKing:darkKing;
		Square kingsSquare = BoardManager.findPiece(k);
		Map<Piece, PieceBlockers> attackers = allAttackers.get(kingsSquare);
		for(Piece p: attackers.keySet()){
			if(!inCheck){
				inCheck = p.teamId != teamToCheck && attackers.get(p).getNumBlockers() == 0;
			}
		}
		return inCheck;
	}
	
	public static boolean willBeInCheck(int teamToCheck, Piece p, Square moveTo){
		boolean inCheck = false;
		King k = (lightKing.teamId == teamToCheck)?lightKing:darkKing;
		Square kingsSquare = (p.equals(k))?moveTo:BoardManager.findPiece(k);
		Map<Piece, PieceBlockers> atkrs = allAttackers.get(kingsSquare);
		for(Piece piece : atkrs.keySet()){
			int numBlockers = atkrs.get(piece).getNumBlockers();
			if(!inCheck && numBlockers <= 1 && piece.teamId != teamToCheck){
				inCheck = (numBlockers == 0 && (p.equals(k) || !moveBlocksCheck(piece, p, moveTo, kingsSquare)) ) || 
						((numBlockers == 1 && ((atkrs.get(piece).hasBlocker(p)) && squareLeadsToKingSquare(BoardManager.findPiece(p), moveTo, kingsSquare, piece) ||
						(p.equals(k) && moveTo.hasOccupant() && atkrs.get(piece).hasBlocker(moveTo.getOccupant()))))); 
			}
		}
		return inCheck;
	}
	
	public static boolean isInCheckmate(int teamToCheck){
		boolean result = true;
		King k = (lightKing.teamId == teamToCheck)?lightKing:darkKing;
		
		Set<Square> moves = pieceInfo.get(k).getMoves();
		for(Square s: moves){
			if(result && (!s.hasOccupant() || s.hasOccupant() && s.getOccupant().teamId != teamToCheck)){
				result = willBeInCheck(teamToCheck, k, s);
			}
		}
		if(result){
			List<Piece> attacking = new ArrayList<>();
			Map<Piece, PieceBlockers> attackers = allAttackers.get(BoardManager.findPiece(k));
			for(Piece p: attackers.keySet()){
				if(p.teamId != teamToCheck && attackers.get(p).getNumBlockers() == 0){
					attacking.add(p);
				}
			}
			result = !canPiecesBlock(attacking, BoardManager.findPiece(k), teamToCheck);
		}
		return result;
	}
	
	private static boolean canPiecesBlock(List<Piece> attacking, Square kingSqr, int teamId){
		boolean result = false;
		Piece currPiece = attacking.get(0);
		//An ally piece can capture the enemy piece
		if(attacking.size() < 2){
			Set<Piece> attackers = allAttackers.get(BoardManager.findPiece(currPiece)).keySet();
			for(Piece p: attackers){
				if(!result){
					result = p.teamId == teamId && allAttackers.get(BoardManager.findPiece(currPiece)).get(p).getNumBlockers() == 0 && !willBeInCheck(teamId, p, BoardManager.findPiece(currPiece));
				}
			}
		}
		if(!result && attacking.size() < 2){
			Square start = pieceInfo.get(currPiece).getOriginOf(kingSqr);
			result = canAllyBlock(teamId, currPiece, start, kingSqr);
		}
		return result;
	}
	
	private static boolean canAllyBlock(int teamId, Piece attacker, Square start, Square king){
		boolean result = false;
		Square curr = start;
		int add = (int)(-BoardManager.getBoardLength()*2*(teamId-.5f));
		Square possPawnSqr = BoardManager.getSquare(curr.getId()+add);
		Set<Piece> pieces;
		while(!result && curr != null && !curr.equals(king)){
			pieces = allAttackers.get(curr).keySet();
			if(possPawnSqr != null){
				Piece maybePawn = possPawnSqr.getOccupant();
				result = maybePawn != null && maybePawn.teamId == teamId && maybePawn.boardId == 'p';
			}
			for(Piece p: pieces){
				if(!result){
					result = (allAttackers.get(curr).get(p).getNumBlockers() == 0 && p.teamId == teamId && p.boardId != 'p' && p.boardId != 'k');
				}
			}
			curr = pieceInfo.get(attacker).getNextSquare(curr);
			possPawnSqr = BoardManager.getSquare(curr.getId()+add);
		}
		return result;
	}
	
	private static boolean moveBlocksCheck(Piece attacker, Piece blocking, Square blockingSquare, Square kingSquare){
		boolean blocksCheck = false;
		Square curr = blockingSquare;
		blocksCheck = BoardManager.findPiece(attacker).equals(blockingSquare);
		while(!blocksCheck && curr != null){
			blocksCheck = curr.equals(kingSquare);
			curr = pieceInfo.get(attacker).getNextSquare(curr);
		}
		return blocksCheck;
	}
	
	private static boolean squareLeadsToKingSquare(Square start, Square end, Square king, Piece toFollow){
		boolean found = false;
		PieceInfo p = pieceInfo.get(toFollow);
		Square curr = start;
		while(!found && curr != null && p != null){
			found = (curr.equals(king));
			curr = p.getNextSquare(curr);
			if(curr != null && curr.equals(end)){
				curr = null;
			}
		}
		return found;
	}
	
	/*public static void setNextSquare(Piece p, Square start, Square next){
		pieceInfo.get(p).putSquare(start, next);
	}*/
	
	public static void pieceWasTaken(Piece p){
		clearAttacks(p);
		Set<Piece> notBlocked = pieceInfo.get(p).getImBlockingKeys();
		for(Piece pc: notBlocked){
			for(Square s: pieceInfo.get(p).getSquaresImBlockingForPiece(pc)){
				allAttackers.get(s).get(pc).removeBlocker(p);
			}
		}
	}
	
	
	
	
	
}
