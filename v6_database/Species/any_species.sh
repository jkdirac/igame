file = [any_species.xml]

MoDeL
{
	species id = [any_species], name = [any species]
	{
		interface
		{
			url:[http://2010.igem.org/Team:USTC_Software];
			shortDesc:[species template for anything];
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
							partReference:[ANY];
							partLabel:[ANY];
							partType:[];
							partCategory:[substituent];
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
			referencedReaction:[tm_dilution] speciesType = [reactant];
		}
	}
}

