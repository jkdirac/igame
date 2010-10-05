file = [E_coli_cell.xml]

MoDeL
{
	species id = [E_coli_cell], name = [E.coli the cell itself]
	{
		interface
		{
			url:[http://2010.igem.org/Team:USTC_Software];
			shortDesc:[species contains only the cell of E.coli];
		}
		cnModel
		{
			listOfChains
			{
				chain
				{
					listOfParts
					{
						part
						{
							partReference:[E_coli];
							partLabel:[E_coli];
							partType:[Compartment];
							partCategory:[compartment];
						}
					}
				}
			}
			listOfTrees
			{
			}
		}
		listOfReferencedReactions
		{
			referencedReaction:[amplification_E_coli] speciesType = [modifier];
		}
	}
}

