file = [IPTG.xml]

MoDeL
{
	part
	{
		compound id = [IPTG], name = [IPTG]
		{
			interface
			{
				url:[http://en.wikipedia.org/wiki/Isopropyl_%CE%B2-D-1-thiogalactopyranoside];
				shortDesc:[Isopropyl-beta-D-thiogalactopyranoside, abbreviated IPTG, is a molecular biology reagent];
			}
			listOfConditionalParameters
			{
			}
			listOfReferencedSpecies
			{
				referencedSpecies:[IPTG_molecule] partType = [SmallMolecule];
				referencedSpecies:[IPTGlacI153_4] partType = [SmallMolecule];
			}
		}
	}
}
