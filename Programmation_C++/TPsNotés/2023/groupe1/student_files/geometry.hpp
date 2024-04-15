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
		Segment(K l,K r);
		bool contains(K n) const;
};
#endif
