int alphabeta(state s, int alpha, int beta) {
	if (s.finished()) return s.score();
	for (state t : s.next()) {
		alpha = max(alpha, -alphabeta(t, -beta, -alpha));
		if (alpha >= beta) break;
	}
	return alpha;
}
