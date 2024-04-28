//NOM:
//PRENOM:
//# étudiant:
#ifndef GEOMETRY_HPP
#define GEOMETRY_HPP
template <class K>
class Segment {
	private:
		K left;
		K right;
	public:
		// question 8
		Segment(K l,K r): left(l), right(r) {};
		bool contains(K n) const {	return (left<=n && n<=right); };
};
#endif
