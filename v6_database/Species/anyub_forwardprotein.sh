file = [anyub_forwardprotein.xml]

MoDeL
{
	species id = [anyub_forwardprotein], name = [any unbinded forward protein]
	{
		interface
		{
			url:[http://2010.igem.org/Team:USTC_Software];
			shortDesc:[species template for any forward protein unbinded];
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
							partReference:[ANYUB];
							partLabel:[ANYUB];
							partType:[FowardProtein];
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
			referencedReaction:[tm_degradation] speciesType = [reactant];
		}
	}
}

