file = [ampicillin.xml]

MoDeL
{
	part
	{
		compound id = [ampicillin], name = [ampicillin]
		{
			interface
			{
				url:[http://en.wikipedia.org/wiki/Ampicillin];
				shortDesc:[Ampicillin is a beta-lactam antibiotic that has been used extensively to treat bacterial infections];
			}
			listOfConditionalParameters
			{
			}
			listOfReferencedSpecies
			{
				referencedSpecies:[ampicillin_molecule] partType = [SmallMolecule];
			}
		}
	}
}
