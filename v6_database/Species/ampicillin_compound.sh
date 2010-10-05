file = [ampicillin_compound.xml]

MoDeL
{
	species id = [ampicillin_compound], name = [ampicillin compound itself]
	{
		interface
		{
			url:[http://2010.igem.org/Team:USTC_Software];
			shortDesc:[species contains only the compound of ampicillin];
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
							partReference:[ampicillin];
							partLabel:[ampicillin];
							partType:[Compound];
							partCategory:[compound];
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
			referencedReaction:[deg_ampicillin_by_pSB1A3] speciesType = [reactant];
		}
	}
}
